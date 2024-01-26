package de.agendasoft.personalportal.backend.utils;

import java.io.ByteArrayOutputStream;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServletResponse;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.apache.pdfbox.pdmodel.PDDocument;
import org.apache.pdfbox.pdmodel.PDPage;
import org.apache.pdfbox.pdmodel.PDPageContentStream;
import org.apache.pdfbox.pdmodel.font.PDType1Font;

public class Text2Pdf {

    public final float LINE_HEIGHT = 14.5F;

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

    public void renderJson2Pdf(String sJson, HttpServletResponse response) throws Exception {

        /* performance for a 40MB json string (with newlines 106MB): ca.
         string read from disk in   259 ms
         json prettied in           904
         divided into [] by \n in   1070
         pdf-generated in           4512
         sent-to-browser in         1006 ms (PDF: 31 MB)
         in sum finished in ca.     9 seconds
         */

        ObjectMapper mapper = new ObjectMapper(); // format the json string nicely & pretty with indentation
        Object json = mapper.readValue(sJson, Object.class);
        String fc = mapper.writerWithDefaultPrettyPrinter().writeValueAsString(json);

        String[] lines = fc.split("\\r?\\n");

        int curLine = 0;
        int linesInPage = 0;

        PDDocument pdDocument = new PDDocument();

        PdfPage page = getNewPage(pdDocument, null);

        assert page != null;
        int maxLinesPerPage = (int) ((page.pdPage.getMediaBox().getHeight() - 20) / LINE_HEIGHT) - 1; // should be ca. 50 for A4
        while (curLine < lines.length - 1) {

            // what if lines[curLine] doesn't fit in one line? A line in the PDF can be max. 90 characters long!
            // improvement possibility: calc instead of using the magic number!
            String[] sCurLines = this.splitInParts(lines[curLine++], 90);

            for (String sCurLine : sCurLines) {

                assert page != null;
                page.contentStream.showText(sCurLine);
                page.contentStream.newLine();

                linesInPage++;

                if (linesInPage >= maxLinesPerPage) {
                    linesInPage = 0;
                    page = getNewPage(pdDocument, page);
                }
            }
        }

        assert page != null;
        page.isLastPage = true;
        getNewPage(pdDocument, page);

        @SuppressWarnings("SpellCheckingInspection")
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        pdDocument.save(baos);
        response.setContentType("application/pdf");
        response.setContentLength(baos.size());
        ServletOutputStream out = response.getOutputStream();
        // improvement possibility: stream while creating the PDF, if possible!
        baos.writeTo(out);

        out.flush();

        pdDocument.close();
    }

    private PdfPage getNewPage(PDDocument pdDocument, PdfPage oldPage) throws Exception {

        if (oldPage != null) {
            oldPage.contentStream.endText();
            oldPage.contentStream.close();

            pdDocument.addPage(oldPage.pdPage);
        }

        boolean createNewPage = oldPage == null || !oldPage.isLastPage;

        if (createNewPage) {
            PDPage pdPage = new PDPage();
            PDPageContentStream contentStream = new PDPageContentStream(pdDocument, pdPage);
            contentStream.beginText();
            float ty = pdPage.getMediaBox().getHeight() - 20;  // 20 = some margin!
            contentStream.newLineAtOffset(10, ty);          // set starting position
            contentStream.setLeading(LINE_HEIGHT);             // set the size of the newline
            contentStream.setFont(PDType1Font.COURIER, 11);

            return new PdfPage(pdPage, contentStream);

        } else {
            return null;
        }
    }

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
