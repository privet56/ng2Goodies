package de.gnd.testcTester;

import jakarta.ws.rs.ApplicationPath;
import jakarta.ws.rs.core.Application;
import java.util.HashSet;
import java.util.Set;

@ApplicationPath("/api")
public class HelloApplication extends Application {

 public Set<Class<?>> getClasses() {
    Set<Class<?>> classes = new HashSet<>();
    classes.add(HelloResource.class);
    classes.add(ResponsePhraseInterceptor.class);
    return classes;
  }
}

}