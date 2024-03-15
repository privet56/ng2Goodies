package de.gnd.testcTester;

import jakarta.ws.rs.GET;
import jakarta.ws.rs.Path;
import jakarta.ws.rs.Produces;
import jakarta.ws.rs.core.Response;

@Path("/hello-world")
public class HelloResource {
    @GET
    @Produces("text/plain")
    public Response hello() {
        String env = System.getenv("org.apache.coyote.USE_CUSTOM_STATUS_MSG_IN_HEADER");
        return Response
                .status(MyStatusType.BAD_REQUEST)
                .entity("My Status was " + MyStatusType.BAD_REQUEST.getReasonPhrase() + " -> env: " + env  )
                .build();
    }
}