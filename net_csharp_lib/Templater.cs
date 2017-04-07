using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Service.Updater
{
    class Templater
    {
        public Templater()
        {

        }
        public static string templateWithReflection(object o, string sTmpl, string sAttr2Ignore, string sDef)
        {
            Type type = o.GetType();
            PropertyInfo[] properties = type.GetProperties();

            string returnIfNoTmpl = "";
            foreach (PropertyInfo property in properties)
            {
                if(property.Name.ToLower().Trim().Equals(sAttr2Ignore.ToLower().Trim()))
                {
                    continue;
                }
                if(("<"+property.Name+">").ToLower().Trim().Equals(sAttr2Ignore.ToLower().Trim()))
                {
                    continue;
                }

                Object val = property.GetValue(o, null);
                if (val == null)
                    val = sDef;

                if (string.IsNullOrWhiteSpace(sTmpl))
                {
                    returnIfNoTmpl += ""+property.Name+": "+val.ToString();
                }
                else
                {
                    sTmpl = sTmpl.Replace("<"+ property.Name + ">", val.ToString());
                }
            }

            if (string.IsNullOrWhiteSpace(sTmpl))
            {
                return returnIfNoTmpl;
            }
            else
            {
                return sTmpl;
            }
        }
        public static string templateDynamicObject(DynamicRow o, string sTmpl, string sDef)
        {
            if (string.IsNullOrWhiteSpace(sTmpl))
            {
                return o.getAllAttrs();
            }

            return o.template(sTmpl, sDef);
        }
        public static string replace(string s, string sToBeReplaced, string sNewContent)
        {
            int i = s.IndexOf(sToBeReplaced);
            s.Replace(sToBeReplaced, "");
            return s.Insert(i, sNewContent);
        }
    }
}
