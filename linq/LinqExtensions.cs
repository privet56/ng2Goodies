using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Common;
using System.Data.Linq;
using System.Dynamic;

namespace Extensions
{
    public static class LinqExtensions
    {
        public static IEnumerable<dynamic> ExecuteQuery(this DataContext ctx, string query)
        {
            using (DbCommand cmd = ctx.Connection.CreateCommand())

            {
                cmd.CommandText = query;
                ctx.Connection.Open();
                using (DbDataReader rdr = cmd.ExecuteReader(CommandBehavior.CloseConnection))

                {
                    while (rdr.Read())
                    {
                        dynamic row = new DynamicRow();

                        for (int i = 0; i < rdr.FieldCount; i++)
                        {
                            row[rdr.GetName(i)] = rdr[i];
                        }

                        yield return row;
                    }
                }
            }
        }
    }

    public class DynamicRow : DynamicObject
    {
        private readonly Dictionary<string, object> _data = new Dictionary<string, object>();

        public object this[string propertyName]

        {
            get
            {
                object result = null;
                TryGetMember(propertyName, out result);
                return result;
            }

            set { TrySetMember(propertyName, value); }
        }

        public string getAllAttrs()
        {
            string s = "";
            foreach (KeyValuePair<string, object> _dat in _data)
            {
                s += "" + _dat.Key + "= " + _dat.Value + "\n";
            }
            return s;
        }
        public string getAttr(String sPropName)
        {
            try
            {
                return _data[sPropName].ToString();
            }
            catch (Exception)
            {
                return null;
            }
        }
        public DateTime getAttrAsDateTime(String sPropName)
        {
            return (DateTime)_data[sPropName];
        }

        public override bool TryGetMember(GetMemberBinder binder, out object result)

        {
            return TryGetMember(binder.Name, out result);
        }

        private bool TryGetMember(string propertyName, out object result)

        {
            return _data.TryGetValue(propertyName, out result);
        }

        public override bool TrySetMember(SetMemberBinder binder, object value)
        {
            return TrySetMember(binder.Name, value);
        }

        private bool TrySetMember(string propertyName, object value)
        {
            _data[propertyName] = value;
            return true;
        }
    }
}
