package de.gnd.util.helpers;

import java.util.ArrayList;
import java.util.List;
import org.slf4j.Marker;
import org.slf4j.event.Level;

public class MockLogger implements org.slf4j.Logger {

    public List<String> entries = new ArrayList<>();

    @Override
    public String getName() {
        return null;
    }

    @Override
    public boolean isTraceEnabled() {
        return true;
    }

    @Override
    public void trace(String s) {
        entries.add(Level.TRACE + ": " + s);
    }

    @Override
    public void trace(String s, Object o) {
        entries.add(Level.TRACE + ": " + o + "> " + s);
    }

    @Override
    public void trace(String s, Object o, Object o1) {
        entries.add(Level.TRACE + ": " + o + "> " + o1 + "> " + s);
    }

    @Override
    public void trace(String s, Object... objects) {
        entries.add(Level.TRACE + ": " + s + "> " + objects);
    }

    @Override
    public void trace(String s, Throwable throwable) {
        entries.add(Level.TRACE + ": " + s + "> " + throwable);
    }

    @Override
    public boolean isTraceEnabled(Marker marker) {
        return true;
    }

    @Override
    public void trace(Marker marker, String s) {
        entries.add(Level.TRACE + ": " + s + "> " + marker);
    }

    @Override
    public void trace(Marker marker, String s, Object o) {
        entries.add(Level.TRACE + ": " + s + "> " + marker + "> " + o);
    }

    @Override
    public void trace(Marker marker, String s, Object o, Object o1) {
        entries.add(Level.TRACE + ": " + s + "> " + marker + "> " + o + "> " + o1);
    }

    @Override
    public void trace(Marker marker, String s, Object... objects) {
        entries.add(Level.TRACE + ": " + s + "> " + marker + "> " + objects);
    }

    @Override
    public void trace(Marker marker, String s, Throwable throwable) {
        entries.add(Level.TRACE + ": " + s + "> " + marker + "> " + throwable);
    }

    @Override
    public boolean isDebugEnabled() {
        return true;
    }

    @Override
    public void debug(String s) {
        entries.add(Level.DEBUG + ": " + s);
    }

    @Override
    public void debug(String s, Object o) {
        entries.add(Level.DEBUG + ": " + s + "> " + o);
    }

    @Override
    public void debug(String s, Object o, Object o1) {
        entries.add(Level.DEBUG + ": " + s + "> " + o + "> " + o1);
    }

    @Override
    public void debug(String s, Object... objects) {
        entries.add(Level.DEBUG + ": " + s + "> " + objects);
    }

    @Override
    public void debug(String s, Throwable throwable) {
        entries.add(Level.DEBUG + ": " + s + "> " + throwable);
    }

    @Override
    public boolean isDebugEnabled(Marker marker) {
        return true;
    }

    @Override
    public void debug(Marker marker, String s) {
        entries.add(Level.DEBUG + ": " + s + "> " + marker);
    }

    @Override
    public void debug(Marker marker, String s, Object o) {
        entries.add(Level.DEBUG + ": " + s + "> " + marker + "> " + o);
    }

    @Override
    public void debug(Marker marker, String s, Object o, Object o1) {
        entries.add(Level.DEBUG + ": " + s + "> " + marker + "> " + o + "> " + o1);
    }

    @Override
    public void debug(Marker marker, String s, Object... objects) {
        entries.add(Level.DEBUG + ": " + s + "> " + marker + "> " + objects);
    }

    @Override
    public void debug(Marker marker, String s, Throwable throwable) {
        entries.add(Level.DEBUG + ": " + s + "> " + marker + "> " + throwable);
    }

    @Override
    public boolean isInfoEnabled() {
        return true;
    }

    @Override
    public void info(String s) {
        entries.add(Level.INFO + ": " + s);
    }

    @Override
    public void info(String s, Object o) {
        entries.add(Level.INFO + ": " + s + "> " + o);
    }

    @Override
    public void info(String s, Object o, Object o1) {
        entries.add(Level.INFO + ": " + s + "> " + o + "> " + o1);
    }

    @Override
    public void info(String s, Object... objects) {
        entries.add(Level.INFO + ": " + s + "> " + objects);
    }

    @Override
    public void info(String s, Throwable throwable) {
        entries.add(Level.INFO + ": " + s + "> " + throwable);
    }

    @Override
    public boolean isInfoEnabled(Marker marker) {
        return true;
    }

    @Override
    public void info(Marker marker, String s) {
        entries.add(Level.INFO + ": " + s + "> " + marker);
    }

    @Override
    public void info(Marker marker, String s, Object o) {
        entries.add(Level.INFO + ": " + s + "> " + marker + "> " + o);
    }

    @Override
    public void info(Marker marker, String s, Object o, Object o1) {
        entries.add(Level.INFO + ": " + s + "> " + marker + "> " + o + "> " + o1);
    }

    @Override
    public void info(Marker marker, String s, Object... objects) {
        entries.add(Level.INFO + ": " + s + "> " + marker + "> " + objects);
    }

    @Override
    public void info(Marker marker, String s, Throwable throwable) {
        entries.add(Level.INFO + ": " + s + "> " + marker + "> " + throwable);
    }

    @Override
    public boolean isWarnEnabled() {
        return true;
    }

    @Override
    public void warn(String s) {
        entries.add(Level.WARN + ": " + s);
    }

    @Override
    public void warn(String s, Object o) {
        entries.add(Level.WARN + ": " + s + "> " + o);
    }

    @Override
    public void warn(String s, Object... objects) {
        entries.add(Level.WARN + ": " + s + "> " + objects);
    }

    @Override
    public void warn(String s, Object o, Object o1) {
        entries.add(Level.WARN + ": " + s + "> " + o + "> " + o1);
    }

    @Override
    public void warn(String s, Throwable throwable) {
        entries.add(Level.WARN + ": " + s + "> " + throwable);
    }

    @Override
    public boolean isWarnEnabled(Marker marker) {
        return true;
    }

    @Override
    public void warn(Marker marker, String s) {
        entries.add(Level.WARN + ": " + s + "> " + marker);
    }

    @Override
    public void warn(Marker marker, String s, Object o) {
        entries.add(Level.WARN + ": " + s + "> " + marker + "> " + o);
    }

    @Override
    public void warn(Marker marker, String s, Object o, Object o1) {
        entries.add(Level.WARN + ": " + s + "> " + marker + "> " + o + "> " + o1);
    }

    @Override
    public void warn(Marker marker, String s, Object... objects) {
        entries.add(Level.WARN + ": " + s + "> " + marker + "> " + objects);
    }

    @Override
    public void warn(Marker marker, String s, Throwable throwable) {
        entries.add(Level.WARN + ": " + s + "> " + marker + "> " + throwable);
    }

    @Override
    public boolean isErrorEnabled() {
        return true;
    }

    @Override
    public void error(String s) {
        entries.add(Level.ERROR + ": " + s);
    }

    @Override
    public void error(String s, Object o) {
        entries.add(Level.ERROR + ": " + s + "> " + o);
    }

    @Override
    public void error(String s, Object o, Object o1) {
        entries.add(Level.ERROR + ": " + s + "> " + o + "> " + o1);
    }

    @Override
    public void error(String s, Object... objects) {
        entries.add(Level.ERROR + ": " + s + "> " + objects);
    }

    @Override
    public void error(String s, Throwable throwable) {
        entries.add(Level.ERROR + ": " + s + "> " + throwable);
    }

    @Override
    public boolean isErrorEnabled(Marker marker) {
        return true;
    }

    @Override
    public void error(Marker marker, String s) {
        entries.add(Level.ERROR + ": " + s + "> " + marker);
    }

    @Override
    public void error(Marker marker, String s, Object o) {
        entries.add(Level.ERROR + ": " + s + "> " + marker + "> " + o);
    }

    @Override
    public void error(Marker marker, String s, Object o, Object o1) {
        entries.add(Level.ERROR + ": " + s + "> " + marker + "> " + o + "> " + o1);
    }

    @Override
    public void error(Marker marker, String s, Object... objects) {
        entries.add(Level.ERROR + ": " + s + "> " + marker + "> " + objects);
    }

    @Override
    public void error(Marker marker, String s, Throwable throwable) {
        entries.add(Level.ERROR + ": " + s + "> " + marker + "> " + throwable);
    }
}
