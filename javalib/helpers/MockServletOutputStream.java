package de.gnd.util.helpers;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import javax.servlet.WriteListener;

public class MockServletOutputStream extends javax.servlet.ServletOutputStream {

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
    }

    @Override
    public void close() throws IOException {
        this.baos.close();
        super.close();
    }

    public void reset() {
        baos = new ByteArrayOutputStream();
    }

    public String getAsText() {
        return baos.toString();
    }
}
