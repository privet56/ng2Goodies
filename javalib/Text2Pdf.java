package de.gnd;

import java.io.ByteArrayOutputStream;
import java.io.OutputStream;
import javax.servlet.ServletResponse;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.apache.pdfbox.pdmodel.PDDocument;
import org.apache.pdfbox.pdmodel.PDPage;
import org.apache.pdfbox.pdmodel.PDPageContentStream;
import org.apache.pdfbox.pdmodel.common.PDRectangle;
import org.apache.pdfbox.pdmodel.font.PDType1Font;

public class Text2Pdf {

    public static final float LINE_HEIGHT = 14.5F;
    public static final int FONT_SIZE = 11;
    public static final int MARGIN = 15;

    // we need fixed width chars to calc max. maxCharacterPerPdfLine (otherwise we would have to use FONT.getStringWidth(s)):
    // eg. float myStringWidthInPdf = FONT_SIZE * FONT.getStringWidth(myString) / 1000;
    public static final PDType1Font FONT = PDType1Font.COURIER;

    protected static final ObjectMapper OBJECT_MAPPER = new ObjectMapper();

    // setup as much as possible statically, to speed up!
    public static float CHAR_WIDTH = FONT.getFontDescriptor().getFontBoundingBox().getWidth() / 1000 * FONT_SIZE;


    public static class PdfPage {

        public PdfPage(PDPage pdPage, PDPageContentStream contentStream) {
            this.pdPage = pdPage;
            this.contentStream = contentStream;
        }

        PDPage pdPage;
        PDPageContentStream contentStream;

        boolean isLastPage;
    }

    public Text2Pdf() {

    }

    /**
     * stream JSON string as PDF into Response, as fast as possible
     * you can also get an sJson as
     * fc = Files.readString(java.nio.file.Path.of("c:\\Entwicklung\\tasks\\ELE-2661\\import (74).json"), StandardCharsets.UTF_8);
     */
    public void renderJson2Pdf(String sJson, ServletResponse response) throws Exception {

        /* performance for a 40MB json string (with newlines 106MB): ca.
         string read from disk in   259 ms
         json prettied in           904
         divided into [] by \n in   1070
         pdf-generated in           4512
         sent-to-browser in         1006 ms (PDF: 31 MB)
         in sum finished in ca.     9 seconds
         */

        // 1. format JSON to pretty
        Object json = OBJECT_MAPPER.readValue(sJson, Object.class);
        String fc = OBJECT_MAPPER.writerWithDefaultPrettyPrinter().writeValueAsString(json);

        // 2. split text into lines (these will build the text lines in the PDF
        String[] lines = fc.split("\\r?\\n");

        int curLine = 0;
        int linesInPage = 0;

        try (PDDocument pdDocument = new PDDocument()) {

            PdfPage page = setupPage(pdDocument, null);

            @SuppressWarnings("DataFlowIssue")
            float pageWidth = page.pdPage.getMediaBox().getWidth();

            // ca. pageWith: 612, charWidth: 8.1 -> maxCharPerPdfLine 75.3
            int maxCharacterPerPdfLine = (int) ((pageWidth + MARGIN + MARGIN) / CHAR_WIDTH);

            int maxLinesPerPage = (int) ((page.pdPage.getMediaBox().getHeight() - MARGIN) / LINE_HEIGHT) - 1; // ca 50 for A4

            // 3. build pages of the PDF
            while (curLine < lines.length) {

                // what if lines[curLine] doesn't fit in one line? A line in the PDF can be max. 80 characters long!
                String[] sCurLines = this.splitInParts(lines[curLine++], maxCharacterPerPdfLine);

                for (String sCurLine : sCurLines) {

                    //noinspection DataFlowIssue
                    page.contentStream.showText(sCurLine);
                    page.contentStream.newLine();

                    linesInPage++;

                    if (linesInPage >= maxLinesPerPage) {
                        linesInPage = 0;
                        page = setupPage(pdDocument, page);
                    }
                }
            }

            //noinspection DataFlowIssue
            page.isLastPage = true;
            setupPage(pdDocument, page);

            // 4. stream finished PDF into response
            try (@SuppressWarnings("SpellCheckingInspection") ByteArrayOutputStream baos = new ByteArrayOutputStream()) {

                baos.flush();
                pdDocument.save(baos);

                response.setContentType("application/pdf");
                response.setContentLength(baos.size());
                OutputStream out = response.getOutputStream();
                // improvement possibility: stream **while creating** the PDF, if possible!?
                baos.writeTo(out);

                out.flush();
            }
        }
    }

    private PdfPage setupPage(PDDocument pdDocument, PdfPage oldPage) throws Exception {

        if (oldPage != null) {
            oldPage.contentStream.endText();
            oldPage.contentStream.close();

            pdDocument.addPage(oldPage.pdPage);
        }

        boolean createNewPage = oldPage == null || !oldPage.isLastPage;

        if (createNewPage) {
            PDPage pdPage = new PDPage();
            pdPage.setMediaBox(PDRectangle.A4);
            PDPageContentStream contentStream = new PDPageContentStream(pdDocument, pdPage);
            contentStream.beginText();

            float startX = pdPage.getMediaBox().getLowerLeftX() + MARGIN;
            float startY = pdPage.getMediaBox().getUpperRightY() - MARGIN;

            contentStream.newLineAtOffset(startX, startY);     // set starting position
            contentStream.setLeading(LINE_HEIGHT);             // set the size of the newline
            contentStream.setFont(FONT, FONT_SIZE);

            return new PdfPage(pdPage, contentStream);

        } else {
            return null;
        }
    }

    /**
     * split a long string into a string[] with max. string length per array element
     */
    public String[] splitInParts(String s, int partLength) {
        int len = s.length();

        // Number of parts
        @SuppressWarnings("SpellCheckingInspection")
        int nparts = (len + partLength - 1) / partLength;
        String[] parts = new String[nparts];

        // Break into parts
        int offset = 0;
        int i = 0;
        while (i < nparts) {
            parts[i] = s.substring(offset, Math.min(offset + partLength, len));
            offset += partLength;
            i++;
        }

        return parts;
    }
}
