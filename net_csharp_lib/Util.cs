using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;

namespace Lib.DataModel
{
    public class Util
    {
        public static readonly string __separator = "------------------------------------------------------------";
        public static string makeAbsUrl(string url)
        {
            if (!string.IsNullOrWhiteSpace(url))
            {
                if (!url.ToLower().StartsWith("http://") && !url.ToLower().StartsWith("https://"))
                    url = "http://" + url;
            }
            return url;
        }
        public static void logTo(string s)
        {
            if (!System.Diagnostics.Debugger.IsAttached)
            {
                return;
            }
            string fn = "c:/temp/.log";
            using (StreamWriter outputFile = new StreamWriter(fn, true/*append*/))
            {
                outputFile.WriteLine(s);
            }
        }
        public static string[] getFileContentLines(string sAbsFN)
        {
#if SILVERLIGHT
            return null;
#else
        //List<String> afc = new List<string>();
        string[] lines = System.IO.File.ReadAllLines(sAbsFN);
        return lines;
#endif
        }
        private object getAttr(object msg, string sPropName)
        {
            Type type = msg.GetType();
            PropertyInfo i = type.GetProperty(sPropName);
            Object val = i.GetValue(msg, null);
            return val;
        }
        private int countEnumerable(IEnumerable<dynamic> datas)
        {
            try
            {
                int i = 0;
                foreach (dynamic data in datas)
                {
                    i++;
                }
                return i;
            }
            catch(Exception)
            {
                return 0;
            }
        }

        private int getAttrCount(object o)
        {
            Type type = o.GetType();
            PropertyInfo[] properties = type.GetProperties();

            int attrs = 0;
            foreach (PropertyInfo property in properties)
            {
                Object val = property.GetValue(o, null);
                if (val != null)
                {
                    attrs++;
                }
            }

            return attrs;
        }

        private string sendEmail(string sEmail, string emailContent, out bool ok, Object notiResult)
        {
            String sMsg = "";
            try
            {
                using (MailMessage msg = new MailMessage())
                {
                    // msg.From is defined by mailSettings in app.config files
                    msg.To.Add(new MailAddress(sEmail));

                    msg.SubjectEncoding = System.Text.Encoding.UTF8;
                    msg.Subject = string.IsNullOrWhiteSpace(notiResult.NotificationMsg) ? "NOTIFICATION" : notiResult.NotificationMsg;

                    msg.BodyEncoding = System.Text.Encoding.UTF8;
                    msg.Body = emailContent;

                    // The problem here is that in .NET 3.5 the SmtpClient never sends the QUIT 
                    // command so the connection is NOT gracefully closed. In .NET 4.0
                    // this bug has been fixed by having SmtpClient implement IDisposable.
                    SmtpClient client = null;
                    if (!System.Diagnostics.Debugger.IsAttached)
                    {
                        client = new SmtpClient();
                    }
                    else
                    {
                        client = new SmtpClient("mail.mycompany.de");
                        client.Port = 25;
                        client.UseDefaultCredentials = true;
                        msg.From = new MailAddress("me@mycompany.com");
                        //client.Credentials = new NetworkCredential("username", "password");
                    }
                    using (client as IDisposable)
                    {
                        client.Send(msg);
                        ok = true;
                    }
                }
            }
            catch (Exception ex)
            {
                TraceLog.Log(ex, "UpdateService.notificator.sendNotifications.sendEmail");

                //Der SMTP-Host wurde nicht angegeben -->
                //<smtp deliveryMethod = "Network" from = "me@mycompany.com" >
                    //<network
                        //host = "mail.mycompany.de"
                        //port = "25"
                        //defaultCredentials = "true"
                    ///>

                sMsg += "EXCEPTION3:" + ex.Message + "\n" + ex.StackTrace + "\n";
                sMsg += " !sendEmail TO:'" + sEmail + "'\n";
                sMsg += " !sendEmail CONTENT:#################################\n" + emailContent+"\n#################################\n";
                ok = false;
            }

            return sMsg;
        }

    }
    public class AttrMapper<T> where T : new()
    {
        public List<T> varList2o(IEnumerable<dynamic> l, Dictionary<String, String> attrName2AttrName)
        {
            List<T> ol = new List<T>();
            T o = new T();  //'where T : new()' defines that we require T to have a default constructor

            Type type = o.GetType();
            PropertyInfo[] properties = type.GetProperties();

            int i = -1;

            foreach (dynamic v in l)
            {
                i++;
                ol.Add(var2o(v, i, attrName2AttrName, type, properties));
            }
            return ol;
        }

        public T var2o(dynamic v, int i, Dictionary<String, String> attrName2AttrNames, Type type, PropertyInfo[] properties)
        {
            T o = new T();

            {   //1: copy attrs which have the same name
                foreach (PropertyInfo property in properties)
                {
                    Object val = v.getAttrNative(property.Name);
                    if (val == null)
                        continue;
                    if (val is System.DBNull)
                        continue;
                    property.SetValue(o, val, null);
                }
            }
            {   //2: copy attrs with different names
                foreach(KeyValuePair<string, string> attrName2AttrName in attrName2AttrNames)
                {
                    Object val = v.getAttrNative(attrName2AttrName.Key);
                    if (val == null)
                        continue;
                    if (val is System.DBNull)
                        continue;
                    PropertyInfo property = type.GetProperty(attrName2AttrName.Value);
                    property.SetValue(o, val, null);
                }
            }
            /*
            if((i > 1064) && (i < 1069))
            {
                logTo("-------------------START(" + i + ")");
                string sAllAttrsWithType = v.getAllAttrsWithType();
                logTo(sAllAttrsWithType);
                logTo("-------------------END--(" + i + ")");
            }
            */
            return o;
        }
    }
}
