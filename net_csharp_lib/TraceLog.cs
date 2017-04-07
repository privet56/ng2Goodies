using System;
using System.Text;
using System.Collections;
using System.IO;

namespace Lib.TraceLog
{
    /// <summary>
    /// Provides logging methods to log exceptions using System.Diagnostics.Trace functionality.
    /// To configure TraceLog in your project provide a system.diagnostics section in your config file:
    /// <system.diagnostics>
    /// <switches>
    ///   <!-- one of Off, Error, Warning, Info, Verbose -->
    ///   <add name="TraceLogSwitch" value="Error" />
    /// </switches>
    /// <trace autoflush="true">
    ///   <listeners>
    ///     <add initializeData="logs\TraceLog.svclog"
    ///          type="System.Diagnostics.XmlWriterTraceListener"
    ///          traceOutputOptions="ProcessId, ThreadId"
    ///          name="debugTraceOutput"/>
    ///     <remove name="Default"/>
    ///   </listeners>
    /// </trace>
    /// </system.diagnostics>
    /// </summary>
    public static class TraceLog
    {
        /// <summary>
        /// The trace level of this TraceLogSwitch is configured in the application's config file.
        /// </summary>
        public static System.Diagnostics.TraceSwitch TraceLogSwitch = new System.Diagnostics.TraceSwitch("TraceLogSwitch", "Trace switch for TraceLog methods.", "Error");

        public static void Log(string information)
        {
            if (information != null)
            {
                if (TraceLogSwitch.TraceInfo)
                {
                    System.Diagnostics.Trace.TraceInformation(information);
                }
            }
        }

        public static void Log(Exception exception)
        {
            Log(exception, null);
        }

        public static void Log(Exception exception, string note)
        {
            Log(exception, note, false);
        }

        public static void Log(Exception exception, string note, bool logDetails)
        {
            if (exception != null && TraceLogSwitch.TraceError)
            {
                LogInternal(exception, note);
                if (logDetails)
                {
                    LogDetails(exception);
                }
            }
        }

        private static void LogInternal(Exception exception, string note)
        {
            System.Diagnostics.Trace.TraceError("{1}: {0}; {2}", exception.Message, exception.GetType().FullName, note);
            if (exception.InnerException != null)
            {
                System.Diagnostics.Trace.TraceError("{1}: {0}", exception.InnerException.Message, "InnerException: " + exception.InnerException.GetType().FullName);
            }
        }

        private static void LogDetails(Exception exception)
        {
            System.Diagnostics.Trace.TraceError(" {1}: {0}", exception.TargetSite, "TargetSite");
            System.Diagnostics.Trace.TraceError(" {1}: {0}", exception.Source, "Source");
            if (exception.Data != null)
            {
                StringBuilder sb = new StringBuilder();
                foreach (DictionaryEntry pair in exception.Data)
                {
                    sb.AppendFormat("{0}={1}, ", pair.Key, pair.Value);
                }
                System.Diagnostics.Trace.TraceError(" {1}: {0}", sb.ToString(), "Data");
            }
        }

        public static bool logTo(string s, bool bForce=false)
        {
            if (!bForce && !System.Diagnostics.Debugger.IsAttached)
            {
                Log(s);
                return false;
            }
            string fn = "c:/temp/.log";
            try
            {
                using (StreamWriter outputFile = new StreamWriter(fn, true/*append*/))
                {
                    outputFile.WriteLine(s);
                }
                return true;
            }
            catch(Exception e)
            {
                //eg file is opened exclusively by another app :-(
                //eg concurrent eg calls (from the html5 client)
                return false;
            }
        }
    }
}
