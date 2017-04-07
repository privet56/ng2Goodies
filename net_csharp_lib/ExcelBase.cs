using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Office.Interop.Excel;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Reflection;
using System.Threading;

namespace CCFTools
{
    public class ExcelBase
    {
        [DllImport("user32.dll")]
        private static extern UInt32 GetWindowThreadProcessId(IntPtr hWnd, out UInt32 ProcessId);

        private Application pExcel = new Application();
        public Application oExcel
        {
            get
            {
                return pExcel;
            }
        }

        protected static System.Object synchronizer = new System.Object();

        public ExcelBase()
        {
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US"); 
        }

        public void open(string filePath)
        {
            lock (synchronizer)
            {
                setEnableEvents(false);

                System.Globalization.CultureInfo oldCi = System.Threading.Thread.CurrentThread.CurrentCulture;

                try
                {
                    System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");

                    oExcel.Workbooks.Open(filePath,
                        Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, 
                        Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value);

                    // System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;
                    // Don't set the old locale back because we need it for other derived classes also.
                }
                catch (Exception e)
                {
                    System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;
                    throw e;
                }

                setEnableEvents(true);

            }

        }

        public void save(string filePath)
        {
            lock (synchronizer)
            {
                setEnableEvents(false);

                System.Globalization.CultureInfo oldCi = System.Threading.Thread.CurrentThread.CurrentCulture;

                try
                {
                    System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");

                    oExcel.ActiveWorkbook.SaveAs(filePath, oExcel.ActiveWorkbook.FileFormat, Missing.Value, Missing.Value, Missing.Value, Missing.Value, XlSaveAsAccessMode.xlExclusive, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value);

                    System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;
                }
                catch (Exception e)
                {
                    System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;
                    throw e;
                }

                setEnableEvents(true);
            }
        }

        public void quit()
        {
            System.Globalization.CultureInfo oldCi = System.Threading.Thread.CurrentThread.CurrentCulture;
            try
            {

                setEnableEvents(false);
                setUserControl(false);
                setDisplayAlerts(false);

                System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
                
                pExcel.Quit();
                
                System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;

                setEnableEvents(true);
            }
            catch {
                System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;
            }
            // If the Excel process is still alive, kill it
            try
            {
                int hWnd = pExcel.Hwnd;
                UInt32 processId;
                UInt32 threadId = GetWindowThreadProcessId(new IntPtr(hWnd), out processId);
                Process pro = Process.GetProcessById((int)processId);
                pro.Kill();
                pro.Dispose();
                pro = null;
            }
            catch { }
            pExcel = null;
        }

        protected void setVisible(Boolean b)
        {
            System.Globalization.CultureInfo oldCi = System.Threading.Thread.CurrentThread.CurrentCulture;
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");

            oExcel.Visible = b;

            System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;
        }

        protected void setScreenUpdating(Boolean b)
        {
            System.Globalization.CultureInfo oldCi = System.Threading.Thread.CurrentThread.CurrentCulture;
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");

            oExcel.ScreenUpdating = b;

            System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;
        }

        protected void setUserControl(Boolean b)
        {
            System.Globalization.CultureInfo oldCi = System.Threading.Thread.CurrentThread.CurrentCulture;
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");

            oExcel.UserControl = b;

            System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;
        }

        protected void setDisplayAlerts(Boolean b)
        {
            System.Globalization.CultureInfo oldCi = System.Threading.Thread.CurrentThread.CurrentCulture;
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");

            oExcel.DisplayAlerts = b;

            System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;
        }

        protected void setEnableEvents(Boolean b)
        {
            System.Globalization.CultureInfo oldCi = System.Threading.Thread.CurrentThread.CurrentCulture;
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");

            oExcel.Application.EnableEvents = b;

            System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;
        }


    }
}
