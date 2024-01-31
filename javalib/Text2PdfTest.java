package de.gnd;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import javax.servlet.ServletResponse;
import javax.servlet.WriteListener;
import de.gnd.Text2Pdf;
import mockit.Expectations;
import mockit.Mocked;
import org.apache.pdfbox.pdmodel.PDDocument;
import org.apache.pdfbox.text.PDFTextStripper;
import org.junit.Assert;
import org.junit.Test;

@SuppressWarnings("SimplifiableAssertion")
public class Text2PdfTest {

    public static class MockServletOutputStream extends javax.servlet.ServletOutputStream {

        public ByteArrayOutputStream baos = new ByteArrayOutputStream();

        @Override
        public boolean isReady() {
            return true;
        }

        @Override
        public void setWriteListener(WriteListener writeListener) {

        }

        @Override
        public void write(int b) throws IOException {
            baos.write(b);
            ;
        }
    }

    @Test
    public void toSplitInParts() {

        Text2Pdf text2Pdf = new Text2Pdf();
        String[] parts;

        parts = text2Pdf.splitInParts("aa", 3);
        Assert.assertTrue(parts.length == 1);

        parts = text2Pdf.splitInParts("aaa", 3);
        Assert.assertTrue(parts.length == 1);

        parts = text2Pdf.splitInParts("aaabbbcccd", 3);
        Assert.assertTrue(parts.length == 4);
        Assert.assertTrue(parts[0].equals("aaa"));
        Assert.assertTrue(parts[1].equals("bbb"));
        Assert.assertTrue(parts[2].equals("ccc"));
        Assert.assertTrue(parts[3].equals("d"));
    }

    @Test
    public void toRenderJson2Pdf(@Mocked ServletResponse response) throws Exception {
        Text2Pdf text2Pdf = new Text2Pdf();

        try (MockServletOutputStream outputStream = new MockServletOutputStream()) {

            new Expectations() {{
                response.getOutputStream();
                result = outputStream;
            }};

            text2Pdf.renderJson2Pdf(
                    "{\"my_json_variable\": \"123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789\"}",
                    response);

            try (PDDocument pdDocument = PDDocument.load(outputStream.baos.toByteArray())) {
                String content = new PDFTextStripper().getText(pdDocument);

                String[] lines = content.split("\\r?\\n");

                Assert.assertTrue(lines.length == 4); // { and } and 2 lines for "my_json_variable"
                Assert.assertTrue(lines[0].equals("{"));
                Assert.assertTrue(lines[lines.length - 1].equals("}"));
            }
        }
    }
}
