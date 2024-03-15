package de.gnd.testcTester;

import jakarta.ws.rs.core.Response;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class HelloResourceTest {

    @Test
    void helloReturnsBadRequestResponse() {
        // Given
        HelloResource helloResource = new HelloResource();

        // When
        Response response = helloResource.hello();

        // Then
        assertEquals(Response.Status.BAD_REQUEST.getStatusCode(), response.getStatus());
        assertEquals("My Status was " + MyStatusType.BAD_REQUEST.getReasonPhrase(), response.getEntity());
        assertEquals( "PASSWORD_EXISTS", response.getStatusInfo().getReasonPhrase());
    }
}