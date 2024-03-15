package de.gnd.testcTester;

import io.restassured.RestAssured;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;
import org.testcontainers.containers.GenericContainer;
import org.testcontainers.containers.wait.strategy.Wait;
import org.testcontainers.junit.jupiter.Container;
import org.testcontainers.junit.jupiter.Testcontainers;
import org.testcontainers.utility.MountableFile;

import static io.restassured.RestAssured.given;
import static org.junit.jupiter.api.Assertions.assertTrue;

@Testcontainers
public class BasicApplicationIT {

    @Container
    GenericContainer microContainer = new GenericContainer("payara/micro:latest").withExposedPorts(8080).withEnv("org.apache.coyote.USE_CUSTOM_STATUS_MSG_IN_HEADER", "true").withCopyFileToContainer(MountableFile.forHostPath("./target/restresult-1.0-SNAPSHOT.war"), "/opt/payara/deployments/app.war").waitingFor(Wait.forLogMessage(".* Payara Micro .* ready in .*\\s", 1)).withCommand("--deploy /opt/payara/deployments/app.war --contextRoot /");

    @BeforeEach
    public void setup() {
        RestAssured.baseURI = "http://localhost";
        RestAssured.port = microContainer.getMappedPort(8080);
    }

    @Test
    public void helloResourceReturns400() {
        given().when().get("/api/hello-world").then().statusCode(400);
    }


    @Test
    public void helloResourceReturnsStatusLine() {
        given().when().get("/api/hello-world").then().statusLine(Matchers.equalTo("HTTP/1.1 " + MyStatusType.BAD_REQUEST.getStatusCode() + " " + MyStatusType.BAD_REQUEST.getReasonPhrase()));
    }

    @Test
    public void helloResourceReturnsBody() {
        given().when().get("/api/hello-world").then().body(Matchers.equalTo("My Status was " + MyStatusType.BAD_REQUEST.getReasonPhrase() + " -> env: true"));
    }

    @Test
    @Disabled
    public void checkContainerIsRunning() {
        assertTrue(microContainer.isRunning());
    }
}
