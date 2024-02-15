package de.gnd.util;

import java.io.IOException;
import java.io.Reader;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.time.temporal.Temporal;
import java.util.Iterator;
import java.util.List;
import java.util.function.Supplier;
import java.util.stream.Collector;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;
import javax.json.JsonObject;
import javax.persistence.Tuple;
import javax.persistence.TupleElement;
import javax.validation.constraints.NotNull;
import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ArrayNode;
import com.fasterxml.jackson.databind.node.JsonNodeFactory;
import com.fasterxml.jackson.databind.node.ObjectNode;
import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.tuple.Pair;
import org.slf4j.Logger;

public final class JsonUtils {
    public static final ObjectMapper OBJECT_MAPPER;


    static {
        OBJECT_MAPPER = new ObjectMapper();
        OBJECT_MAPPER.disable(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES);
    }

    private JsonUtils() {}

    public static JsonNode parse(String json) {
        try {
            return OBJECT_MAPPER.readValue(json, JsonNode.class);
        } catch (IOException e) {
            throw new IllegalArgumentException("cannot parse JSON object", e);
        }
    }

    public static String stringify(@NotNull JsonObject object, boolean maskPassword, @NotNull Logger logger) {
        String sJson = object.toString();
        if (maskPassword) {
            JsonNode node = parse(sJson);
            maskPassword(node, logger);
            sJson = node.toString();
        }
        return sJson;
    }

    private static void maskPassword(JsonNode jsonNode, Logger logger) {

        if (jsonNode == null || jsonNode.isEmpty() || jsonNode.isNull()) {
            return;
        }

        if (!(jsonNode instanceof ObjectNode) && !(jsonNode instanceof ArrayNode)) {
            logger.error("unknown json node: " + jsonNode);
            return;
        }

        if (jsonNode instanceof ObjectNode) {
            String password = JsonUtils.get(jsonNode, Name.Property.PASSWORD, String.class);
            if (!StringUtils.isBlank(password)) {
                JsonUtils.set((ObjectNode) jsonNode, Name.Property.PASSWORD, "masked password with len " + password.length());
            }
        }

        JsonUtils.stream(jsonNode).forEach((JsonNode childNode) -> { // recurse!
            maskPassword(childNode, logger);
        });
    }
}
