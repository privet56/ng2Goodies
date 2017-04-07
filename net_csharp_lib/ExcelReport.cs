using System;
using System.Reflection;
using System.Collections.Generic;
using System.Text;
using Microsoft.Office.Interop.Excel;
using System.Collections;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace CCFTools
{
    public class ExcelReport : ExcelBase
    {
        private string _template;

        public ExcelReport(string template) : base()
        {
            _template = template;
        }

        public void create()
        {

            setVisible(false);
            setScreenUpdating(false);
            setUserControl(false);
            setDisplayAlerts(false);

            setEnableEvents(false);

            //Workaround for a bug in Excel
            System.Globalization.CultureInfo oldCi = System.Threading.Thread.CurrentThread.CurrentCulture;
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");

            oExcel.Workbooks.Add(_template).Activate();

            System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;

            setEnableEvents(true);

        }

        public void importXml(string xmlData, string xmlName)
        {
            System.Globalization.CultureInfo oldCi = System.Threading.Thread.CurrentThread.CurrentCulture;
            try
            {
                setEnableEvents(false);

                System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
                
                XmlMap xmp = oExcel.ActiveWorkbook.XmlMaps.get_Item(xmlName);
                xmp.ImportXml(xmlData, true);

                System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;

                setEnableEvents(true);
            }
            catch (System.Runtime.InteropServices.COMException e)
            {
                System.Threading.Thread.CurrentThread.CurrentCulture = oldCi;
                throw new Exception("Exception loading xml " + xmlName + " to Excel. Does a XmlMap with this name exist in the 'Template.xls'?", e);
            }
        }

        public void show()
        {

            setVisible(true);
            setScreenUpdating (true);
            setUserControl(true);
            setDisplayAlerts(true);

            setEnableEvents(true);


        }

        new public void save(string filePath)
        {
            if (oExcel == null)
            {
                create();
            }
            base.save(filePath);
        }

        new public void quit()
        {
            if (oExcel != null)
            {
                base.quit();
            }
        }
    }
}
