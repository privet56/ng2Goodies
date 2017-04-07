using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.DirectoryServices;

namespace CCFTools
{
    class ADTools
    {
        public static List<UserEntry> findUser(string surName, string firstName, string email)
        {
            List<UserEntry> entries = new List<UserEntry>();

            if (surName == null)
                surName = "";
            if (firstName == null)
                firstName = "";
            if (email == null)
                email = "";

            if (surName.Equals("") && firstName.Equals("") && email.Equals(""))
            {
                MessageBox.Show("Please enter at least one search criterion.");
                return entries;
            }

            if (surName == "")
                surName = "*";
            if (firstName == "")
                firstName = "*";
            if (email == "")
                email = "*";

            //Console.WriteLine(System.Security.Principal.WindowsIdentity.GetCurrent().Name.ToString());

            DirectoryEntry searchRoot = null;
            DirectoryEntry gc = new DirectoryEntry("GC:");
            //gc has only one child
            foreach (DirectoryEntry child in gc.Children)
            {
                searchRoot = child;
            }

            DirectorySearcher objsearch = new DirectorySearcher(searchRoot);
            string root = objsearch.SearchRoot.Path;
            objsearch.Filter = @"(&(objectClass=user)(&(&(sn=" + surName + ")(givenName=" + firstName + "))(mail=" + email + ")))";
            objsearch.SearchScope = System.DirectoryServices.SearchScope.Subtree;
            objsearch.PropertiesToLoad.Add("sn");
            objsearch.PropertiesToLoad.Add("givenname");
            objsearch.PropertiesToLoad.Add("samaccountname");
            objsearch.PropertiesToLoad.Add("department");
            objsearch.PropertiesToLoad.Add("cn");
            objsearch.PropertiesToLoad.Add("telephoneNumber");
            objsearch.PropertiesToLoad.Add("physicalDeliveryOfficeName");
            objsearch.PropertiesToLoad.Add("company");
            objsearch.PropertiesToLoad.Add("name");

            objsearch.PropertyNamesOnly = true;
            objsearch.Sort.Direction = System.DirectoryServices.SortDirection.Ascending;
            objsearch.Sort.PropertyName = "cn";
            SearchResultCollection results = objsearch.FindAll();
            foreach (SearchResult res in results)
            {
                UserEntry entry = new UserEntry();
                DirectoryEntry parent = res.GetDirectoryEntry().Parent;
                while (!parent.SchemaClassName.Equals("domainDNS"))
                {
                    parent = parent.Parent;
                }
                string domainName = (string)parent.Properties["name"].Value;
                entry.domain = domainName.ToUpper();
                entry.email = (string)res.GetDirectoryEntry().Properties["mail"].Value;
                entry.surName = (string)res.GetDirectoryEntry().Properties["sn"].Value;
                entry.firstname = (string)res.GetDirectoryEntry().Properties["givenname"].Value;
                entry.samaccountname = (string)res.GetDirectoryEntry().Properties["samaccountname"].Value;
                entry.department = (string)res.GetDirectoryEntry().Properties["department"].Value;
                entry.cn = (string)res.GetDirectoryEntry().Properties["cn"].Value;
                entry.telephoneNumber = (string)res.GetDirectoryEntry().Properties["telephoneNumber"].Value;
                entry.physicalDeliveryOfficeName = (string)res.GetDirectoryEntry().Properties["physicalDeliveryOfficeName"].Value;
                entry.company = (string)res.GetDirectoryEntry().Properties["company"].Value;
                entry.username = entry.domain + @"\" + entry.samaccountname;

                entries.Add(entry);
            }
            objsearch.Dispose();

            return entries;
        }

        public static UserEntry findUser(string userName)
        {
            return findUser(userName, true);
        }

        public static UserEntry findUser(string userName, bool showFailure)
        {
            UserEntry entry = null;

            if (userName == null)
            {
                if (showFailure)
                    MessageBox.Show("Please enter a user name.");
                return entry;
            }

            string[] sp = userName.Split(new string[] { @"\" }, System.StringSplitOptions.None);

            if (sp.Length != 2)
            {
                if (showFailure)
                    MessageBox.Show(@"Please enter a user name in the format 'GLOBAL-AD\USERNAME'.");
                return entry;
            }

            string searchDomain = sp[0].ToUpper();
            string searchUser = sp[1].ToUpper();

            //Console.WriteLine(System.Security.Principal.WindowsIdentity.GetCurrent().Name.ToString());

            DirectoryEntry searchRoot = null;
            DirectoryEntry gc = new DirectoryEntry("GC:");
            //gc has only one child
            foreach (DirectoryEntry child in gc.Children)
            {
                searchRoot = child;
            }

            DirectorySearcher objsearch = new DirectorySearcher(searchRoot);
            string root = objsearch.SearchRoot.Path;
            objsearch.Filter = @"(&(objectClass=user)(samaccountname=" + searchUser + "))";
            objsearch.SearchScope = System.DirectoryServices.SearchScope.Subtree;
            objsearch.PropertiesToLoad.Add("sn");
            objsearch.PropertiesToLoad.Add("givenname");
            objsearch.PropertiesToLoad.Add("samaccountname");
            objsearch.PropertiesToLoad.Add("department");
            objsearch.PropertiesToLoad.Add("cn");
            objsearch.PropertiesToLoad.Add("telephoneNumber");
            objsearch.PropertiesToLoad.Add("physicalDeliveryOfficeName");
            objsearch.PropertiesToLoad.Add("company");
            objsearch.PropertiesToLoad.Add("name");

            objsearch.PropertyNamesOnly = true;
            objsearch.Sort.Direction = System.DirectoryServices.SortDirection.Ascending;
            objsearch.Sort.PropertyName = "cn";
            SearchResultCollection results = objsearch.FindAll();
            foreach (SearchResult res in results)
            {
                DirectoryEntry parent = res.GetDirectoryEntry().Parent;
                while (!parent.SchemaClassName.Equals("domainDNS"))
                {
                    parent = parent.Parent;
                }
                string domainName = (string)parent.Properties["name"].Value;
                if (domainName.ToUpper().Equals(searchDomain))
                {
                    entry = new UserEntry();
                    entry.domain = domainName.ToUpper();
                    entry.email = (string)res.GetDirectoryEntry().Properties["mail"].Value;
                    entry.surName = (string)res.GetDirectoryEntry().Properties["sn"].Value;
                    entry.firstname = (string)res.GetDirectoryEntry().Properties["givenname"].Value;
                    entry.samaccountname = (string)res.GetDirectoryEntry().Properties["samaccountname"].Value;
                    entry.department = (string)res.GetDirectoryEntry().Properties["department"].Value;
                    entry.cn = (string)res.GetDirectoryEntry().Properties["cn"].Value;
                    entry.telephoneNumber = (string)res.GetDirectoryEntry().Properties["telephoneNumber"].Value;
                    entry.physicalDeliveryOfficeName = (string)res.GetDirectoryEntry().Properties["physicalDeliveryOfficeName"].Value;
                    entry.company = (string)res.GetDirectoryEntry().Properties["company"].Value;
                    entry.username = entry.domain + @"\" + entry.samaccountname;
                    break;
                }
            }
            objsearch.Dispose();

            if (entry == null && showFailure)
            {
                MessageBox.Show("User not found!");
            }

            return entry;
        }

    }



    public class UserEntry
    {
        public string username { get; set; }
        public string cn { get; set; }
        public string surName { get; set; }
        public string firstname { get; set; }
        public string email { get; set; }
        public string department { get; set; }
        public string domain { get; set; }
        public string samaccountname { get; set; }
        public string telephoneNumber { get; set; }
        public string physicalDeliveryOfficeName { get; set; }
        public string company { get; set; }

        public string getText()
        {
            return username + ", " + cn + ", " + department;
        }

        override public string ToString()
        {
            return cn + "; " + department + "; " + physicalDeliveryOfficeName;
        }

        public string getCountryISO2()
        {
            return physicalDeliveryOfficeName.Split('/')[0];
        }
    }


}
