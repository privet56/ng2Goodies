package de.gnd;

import static java.lang.Thread.sleep;
import java.lang.invoke.MethodHandles;
import java.util.function.Supplier;
import jakarta.ejb.LocalBean;
import jakarta.ejb.Stateless;
import jakarta.validation.constraints.NotNull;
import de.gnd.EpochUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

@Stateless
@LocalBean
public class LoggedExecutor {

    private static final Logger LOG = LoggerFactory.getLogger(MethodHandles.lookup().lookupClass());

    /**
     * call this way:
     * this.loggedExecutor.executeAndLog(this, LOG, "myFunctionName", () -> {
     * .    return "result: " + payloadFunction();
     * });
     */
    public boolean executeAndLog(@NotNull Object executor, @NotNull Logger log, @NotNull String functionName,
                                 @NotNull Supplier<String> function) {

        // (a space after @Schedule should ensure easy search-ability in kibana)
        String executedFunction = "@Schedule " + executor.getClass().getSimpleName() + ":" + functionName;

        log(log, executedFunction + " START");

        String result = null;
        boolean ok = false;
        long start = System.currentTimeMillis();

        try {
            result = function.get();
            ok = true;
        } catch (Exception e) {
            result = e.getMessage();
            //noinspection ReassignedVariable
            ok = false;
            // throw e; // don't rethrow = avoid ejb.timer_exceeded_max_deliveries
        } finally {
            long durationMs = (System.currentTimeMillis() - start);
            log(log,
                executedFunction + " END OK: " + ok + "; duration: " + EpochUtils.durationReadable(durationMs) + "; " + result);
        }

        return ok;
    }

    /**
     * manual implementation of something like ~org.eclipse.microprofile.faulttolerance.Retry // @Retry(delay = 5, delayUnit = ChronoUnit.SECONDS)
     *
     * @param delaySeconds between executions
     * @param retryCount   try x times to execute function, try again if throws
     * @param function     throws if fails
     * @param result       can be null; return value of the function
     *                     .
     * @return <b>true</b> = successfully executed;<br> <b>false</b> = threw retryCount-times (independently of the return value of the function)
     * .
     * @code Example: loggedExecutor.retry(
     * <br>&nbsp;&nbsp;    2, // delay 2 secs between executions
     * <br>&nbsp;&nbsp;    3, // try max 3 times
     * <br>&nbsp;&nbsp;    () -> { return tryACall(); },
     * <br>&nbsp;&nbsp;    null);
     */
    public boolean retry(int delaySeconds, int retryCount, @NotNull Supplier<String> function, StringBuffer result) {

        for (int i = 0; i <= retryCount; i++) {

            try {
                String sResult = function.get();
                if ((result != null) && (sResult != null)) {
                    result.append(sResult);
                }
                return true;
            } catch (Exception e) {

                log(LOG, "retry(" + delaySeconds + ", " + retryCount + ") EXC: " + e.getMessage());

                try { // wait delaySeconds seconds
                    sleep(delaySeconds * 1000L);
                } catch (InterruptedException ie) {
                    log(LOG, "retry(" + delaySeconds + ", " + retryCount + ") interrupted: " + ie.getMessage());
                }
            }
        }

        log(LOG, "retry(" + delaySeconds + ", " + retryCount + ") failed");
        return false;
    }

    private void log(Logger log, String s) {
        log.info(s);
    }
}
