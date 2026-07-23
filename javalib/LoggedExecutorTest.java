package de.gnd;

import static java.util.stream.Collectors.counting;
import static java.util.stream.Collectors.groupingBy;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;
import jakarta.ejb.Schedule;
import jakarta.ws.rs.core.Response;
import de.gnd.LoggedExecutor;
import de.gnd.helpers.MockLogger;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.reflections.Reflections;
import org.reflections.scanners.MemberUsageScanner;
import org.reflections.scanners.MethodAnnotationsScanner;
import org.reflections.util.ConfigurationBuilder;

public class LoggedExecutorTest {

    LoggedExecutor loggedExecutor = new LoggedExecutor();

    @Test
    public void testOKExecution() {

        LoggedExecutor loggedExecutor = new LoggedExecutor();
        MockLogger logger = new MockLogger();
        String payload = "someResult";
        boolean ok = false;

        ok = loggedExecutor.executeAndLog(this, logger, "testExecution", () -> {
            return payload;
        });
        Assertions.assertTrue(ok);
        Assertions.assertTrue(logger.hasEntryWithText(payload));
        Assertions.assertTrue(logger.hasEntryWithText("END OK: " + ok));
    }

    @Test
    public void testNotOKExecution() {
        MockLogger logger = new MockLogger();
        String payload = "someResult";
        boolean ok = false;
        boolean hasException = false;
        String exceptionMsg = null;

        try {
            ok = loggedExecutor.executeAndLog(this, logger, "testExecution", () -> {
                throw new NullPointerException(payload);
            });
        } catch (Exception e) {
            exceptionMsg = e.getMessage();
            hasException = true;
        }
        Assertions.assertTrue(exceptionMsg == null);
        Assertions.assertTrue(!ok);
        Assertions.assertTrue(hasException == false);
        Assertions.assertTrue(logger.hasEntryWithText(payload));
        Assertions.assertTrue(logger.hasEntryWithText("END OK: " + ok));
    }

    @Test
    public void testIfClassWithScheduleUsesLoggedExecutor() {

        // pkg should be "de.gnd"
        String pkg = this.getClass().getPackageName().substring(0, this.getClass().getPackageName().lastIndexOf('.'));

        Reflections reflections =
                new Reflections(new ConfigurationBuilder().forPackages(pkg)
                                                          .setScanners(new MethodAnnotationsScanner(), new MemberUsageScanner()));
        Set<Method> methods = reflections.getMethodsAnnotatedWith(Schedule.class);
        Assertions.assertTrue(methods.size() > 3);

        Map<Class, Long> class2FunctionsWithScheduleCount =
                methods.stream().collect(groupingBy(Method::getDeclaringClass, counting()));
        Assertions.assertTrue(class2FunctionsWithScheduleCount.size() > 3);

        Optional<Long> maxScheduleCount = class2FunctionsWithScheduleCount.values().stream().max(Long::compareTo);
        Assertions.assertTrue(maxScheduleCount.get() > 1); // MetricRunner has 3 methods with @Schedule!

        class2FunctionsWithScheduleCount.forEach((Class clazz, Long functionsWithScheduleCount) -> {

            Assertions.assertTrue(functionsWithScheduleCount > 0);

            boolean hasLoggedExecutor = false;
            boolean loggedExecutorUsedAsManyTimesAsScheduledFunctionsAre = false;

            for (Field field : clazz.getDeclaredFields()) {
                field.setAccessible(true);
                Class<?> fieldType = field.getType();
                if (fieldType.isAssignableFrom(LoggedExecutor.class)) {
                    hasLoggedExecutor = true;
                    java.util.Set<java.lang.reflect.Member> usages = reflections.getFieldUsage(field);
                    Assertions.assertTrue(usages.size() > 0);
                    // eg. MetricRunner has 3 @Schedule'd annos -> LoggedExecutor should be used min. 3 times -> usages.size() == 3
                    if (usages.size() >= functionsWithScheduleCount) {
                        loggedExecutorUsedAsManyTimesAsScheduledFunctionsAre = true;
                    }
                    break;
                }
            }
            Assertions.assertTrue(hasLoggedExecutor);
            Assertions.assertTrue(loggedExecutorUsedAsManyTimesAsScheduledFunctionsAre);
        });
    }

    @Test
    public void testRetry() {

        boolean success = false;

        {
            success = loggedExecutor.retry(1, 3, () -> {
                throw new RuntimeException("fail");
            }, null);
            Assertions.assertFalse(success);
        }
        {
            success = loggedExecutor.retry(1, 3, () -> {
                //noinspection Convert2MethodRef
                return Response.Status.OK.name();
            }, null);
            Assertions.assertTrue(success);
        }
        {
            StringBuffer result = new StringBuffer();
            success = loggedExecutor.retry(1, 3, () -> {
                //noinspection Convert2MethodRef
                return Response.Status.OK.name();
            }, result);
            Assertions.assertTrue(success);
            Assertions.assertEquals(Response.Status.OK.name(), result.toString());
        }

        {
            AtomicInteger counter = new AtomicInteger(0);
            StringBuffer result = new StringBuffer();
            success = loggedExecutor.retry(1, 6, () -> {

                if (counter.incrementAndGet() < 3) {
                    throw new RuntimeException("fail");
                }

                return Response.Status.OK.name();
            }, result);
            Assertions.assertTrue(success);
            Assertions.assertEquals(3, counter.get());
            Assertions.assertEquals(Response.Status.OK.name(), result.toString());
        }
    }
}
