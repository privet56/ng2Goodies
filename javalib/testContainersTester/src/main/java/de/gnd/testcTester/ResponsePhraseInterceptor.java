package de.gnd.testcTester;

import jakarta.ws.rs.container.ContainerRequestContext;
import jakarta.ws.rs.container.ContainerResponseContext;
import jakarta.ws.rs.container.ContainerResponseFilter;
import jakarta.ws.rs.ext.Provider;
import java.io.IOException;

@Provider
public class ResponsePhraseInterceptor implements ContainerResponseFilter {

  @Override
  public void filter(
    ContainerRequestContext requestContext,
    ContainerResponseContext responseContext
  ) throws IOException {
    String statusInfo = responseContext.getStatusInfo().getReasonPhrase();
    responseContext.getHeaders().add("X-Reason-Phrase", statusInfo);
  }
}
