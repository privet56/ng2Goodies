package de.gnd.util;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StringReader;
import java.net.URL;
import java.nio.charset.StandardCharsets;
import javax.json.Json;
import javax.json.JsonObject;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.node.ArrayNode;
import com.fasterxml.jackson.databind.node.JsonNodeFactory;
import com.fasterxml.jackson.databind.node.ObjectNode;
import org.apache.commons.lang3.StringUtils;
import org.junit.Assert;
import org.junit.Test;

public class JsonUtilsTest {

    @Test
    public void testStringify() throws IOException {

        MockLogger logger = new MockLogger();
        String sJson;
        JsonObject jsonObject;
        String result;

        sJson = "{\"rhabarber\":\"rapunzel\"}";                                                     // check 0: !maskPassword
        jsonObject = Json.createReader(new StringReader(sJson)).readObject();
        result = JsonUtils.stringify(jsonObject, false, logger);
        Assert.assertTrue(result.startsWith("{"));
        Assert.assertTrue(result.endsWith("}"));
        Assert.assertTrue(result.indexOf("rhabarber") > 0);
        Assert.assertTrue(result.indexOf("rapunzel") > 0);
        Assert.assertTrue(logger.entries.isEmpty());

        sJson = "{\"rhabarber\":\"rapunzel\"}";                                                     // check 1
        jsonObject = Json.createReader(new StringReader(sJson)).readObject();
        result = JsonUtils.stringify(jsonObject, true, logger);
        Assert.assertTrue(result.startsWith("{"));
        Assert.assertTrue(result.endsWith("}"));
        Assert.assertTrue(result.indexOf("rhabarber") > 0);
        Assert.assertTrue(result.indexOf("rapunzel") > 0);
        Assert.assertTrue(logger.entries.isEmpty());

        sJson = "{\"rhabarber\":\"" + Name.Property.PASSWORD + "\"}";                                 // check 2
        jsonObject = Json.createReader(new StringReader(sJson)).readObject();
        result = JsonUtils.stringify(jsonObject, true, logger);
        Assert.assertTrue(result.startsWith("{"));
        Assert.assertTrue(result.endsWith("}"));
        Assert.assertTrue(result.indexOf("rhabarber") > 0);
        Assert.assertTrue(result.indexOf(Name.Property.PASSWORD) > 0);
        Assert.assertTrue(logger.entries.isEmpty());

        sJson = "{\"" + Name.Property.PASSWORD + "\":\"rapunzel\"}";                                 // check 3
        jsonObject = Json.createReader(new StringReader(sJson)).readObject();
        result = JsonUtils.stringify(jsonObject, true, logger);
        Assert.assertTrue(result.startsWith("{"));
        Assert.assertTrue(result.endsWith("}"));
        Assert.assertTrue(result.indexOf(Name.Property.PASSWORD) > 0);
        Assert.assertTrue(result.indexOf("rapunzel") < 0); // replaced!
        Assert.assertTrue(logger.entries.isEmpty());

        jsonObject = Json.createReader(new StringReader(result)).readObject();
        Assert.assertTrue(StringUtils.isNotBlank(jsonObject.getString(Name.Property.PASSWORD)));

        URL url = TestHelper.class.getResource("my.json");                         // check 4
        InputStream stream = url.openStream();
        JsonNode jsonNode = JsonUtils.parse(new InputStreamReader(stream, StandardCharsets.UTF_8));
        ObjectNode child = (ObjectNode) jsonNode.get(Name.Property.PAYLOAD).get("Hierarchy");

        child.put(Name.Property.PASSWORD, Name.Property.PASSWORD + "1");            // add pwd as object

        ArrayNode arrayNode = JsonNodeFactory.instance.arrayNode();
        ObjectNode object = arrayNode.addObject();
        object.put("rhabarber1", "rapunzel");
        object.put(Name.Property.PASSWORD, Name.Property.PASSWORD + "2");           // add pwd as array element
        object.put("rhabarber2", "rapunzel2");
        child.put("someArray", arrayNode);

        sJson = jsonNode.toString();

        Assert.assertTrue(sJson.startsWith("{"));                                      // is input as expected?
        Assert.assertTrue(sJson.endsWith("}"));
        Assert.assertTrue(sJson.indexOf(Name.Property.PASSWORD + "1") > 0);
        Assert.assertTrue(sJson.indexOf(Name.Property.PASSWORD + "2") > 0);
        Assert.assertTrue(sJson.indexOf("rhabarber1") > 0);
        Assert.assertTrue(sJson.indexOf("rhabarber2") > 0);

        jsonObject = Json.createReader(new StringReader(sJson)).readObject();
        result = JsonUtils.stringify(jsonObject, true, logger);
        Assert.assertTrue(result.startsWith("{"));
        Assert.assertTrue(result.endsWith("}"));
        Assert.assertTrue(result.indexOf(Name.Property.PASSWORD) > 0);
        Assert.assertTrue(result.indexOf(Name.Property.PASSWORD + "1") < 0);
        Assert.assertTrue(result.indexOf(Name.Property.PASSWORD + "2") < 0);
        Assert.assertTrue(result.indexOf("rhabarber1") > 0);
        Assert.assertTrue(result.indexOf("rhabarber2") > 0);
        Assert.assertTrue(logger.entries.isEmpty());
    }
}
