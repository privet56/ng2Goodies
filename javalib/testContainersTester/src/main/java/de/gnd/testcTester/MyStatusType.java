package de.gnd.testcTester;

import jakarta.ws.rs.core.Response;

public class MyStatusType implements Response.StatusType {
    public static final MyStatusType OK = new MyStatusType(Response.Status.OK, 200, "OK", "Request was successful");
    public static final MyStatusType CREATED = new MyStatusType(Response.Status.CREATED, 201, "Created", "Resource was created");
    public static final MyStatusType NO_CONTENT = new MyStatusType(Response.Status.NO_CONTENT, 204, "No Content", "Request was successful, but no content was returned");
    public static final MyStatusType BAD_REQUEST = new MyStatusType(Response.Status.BAD_REQUEST, 400, "PASSWORD_EXISTS", "No password was provided");

    private final Response.Status status;
    private final int statusCode;
    private final String reasonPhrase;
    private final String description;

    public MyStatusType(Response.Status status, int statusCode, String reasonPhrase, String description) {
        this.status = status;
        this.statusCode = statusCode;
        this.reasonPhrase = reasonPhrase;
        this.description = description;
    }

    @Override
    public int getStatusCode() {
        return statusCode;
    }

    @Override
    public Response.Status.Family getFamily() {
        return status.getFamily();
    }

    @Override
    public String getReasonPhrase() {
        return reasonPhrase;
    }
}