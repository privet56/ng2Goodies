using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using System.Collections;

namespace CCFTools
{
    public delegate void SaveNeededEventHandler(Object sender, SaveNeededEventArgs e);
    public delegate void CreateNeededEventHandler(Object sender, CreateNeededEventArgs e);
    
    public delegate string UpdateObject(ref object data);
    //public delegate string CreateObject(ref object data);
    public delegate string ValidateObject(object data);

    class ExtendedDataGridView : DataGridView
    {
        //private BindingSource dataBindingSource;
        //private string[] dataProperties;

        public event SaveNeededEventHandler SaveNeeded;
        public event CreateNeededEventHandler CreateNeeded;

        private UpdateObject updateObject;
        //private CreateObject createObject;
        private ValidateObject validateObject;

        private bool onlyAdding;
        public bool OnlyAdding
        {
            get
            {
                return onlyAdding;
            }
            set
            {
                onlyAdding = (bool)value;
            }
        }

        /*
        public object DataBindingSource
        {
            get
            {
                return dataBindingSource;
            }
            set
            {
                dataBindingSource = (BindingSource )value;
                dataBindingSource.CurrentChanged += new EventHandler(dataBindingSource_CurrentChanged);
            }
        }
        */
        void ExtendedDataGridView_CurrentChanged(object sender, EventArgs e)
        {
            BindingSource dataBindingSource = (BindingSource)DataSource;
            if (dataBindingSource.Current == null)
            {
                currentValue = null;
            }
            else
            {
                currentValue = Clone(dataBindingSource.Current);
            }
        }
        
        /*public string[] DataProperties
        {
            get
            {
                return dataProperties;
            }
            set
            {
                dataProperties = value;
            }
        }
         * */
        public UpdateObject UpdateObjectDelegate
        {
            get
            {
                return updateObject;
            }
            set
            {
                updateObject = value;
            }
        }
       public ValidateObject ValidateObjectDelegate
        {
            get
            {
                return validateObject;
            }
            set
            {
                validateObject = value;
            }
        }

        private object currentValue;
        private bool rowCancel;
//        private bool newRow;

        public ExtendedDataGridView()
        {
            this.EditMode = DataGridViewEditMode.EditOnEnter;
            this.VirtualMode = true;
            this.RowLeave += new DataGridViewCellEventHandler(ExtendedDataGridView_RowLeave);
            this.CancelRowEdit += new QuestionEventHandler(ExtendedDataGridView_CancelRowEdit);
            this.RowValidating += new DataGridViewCellCancelEventHandler(ExtendedDataGridView_RowValidating);
            this.DataSourceChanged += new EventHandler(ExtendedDataGridView_DataSourceChanged);
            this.RowEnter += new DataGridViewCellEventHandler(ExtendedDataGridView_RowEnter);
            this.ShowRowErrors = true;
        }

        void ExtendedDataGridView_RowEnter(object sender, DataGridViewCellEventArgs e)
        {
            if (onlyAdding == true)
            {
                this.ReadOnly = false;
                if (this.Rows[e.RowIndex].IsNewRow || this.IsCurrentRowDirty)
                {
                    this.Rows[e.RowIndex].ReadOnly = false;
                }
                else
                {
                    this.Rows[e.RowIndex].ReadOnly = true;
                }
            }
//            else
//            {
//                this.Rows[e.RowIndex].ReadOnly = false;
//            }
        }

        void ExtendedDataGridView_DataSourceChanged(object sender, EventArgs e)
        {
            ((BindingSource)this.DataSource).CurrentChanged += new EventHandler(ExtendedDataGridView_CurrentChanged);
            
        }

        void ExtendedDataGridView_RowValidating(object sender, DataGridViewCellCancelEventArgs e)
        {
            if (rowCancel)
            {
                e.Cancel = true;
                rowCancel = false;
            }
            else
            {
                if (CurrentRow != null)
                    CurrentRow.ErrorText = "";
            }
        }

        void ExtendedDataGridView_CancelRowEdit(object sender, QuestionEventArgs e)
        {
            BindingSource dataBindingSource = (BindingSource)DataSource;

            CopyObject(currentValue, dataBindingSource.Current);

            NotifyCurrentCellDirty(false);
            CurrentRow.ErrorText = "";
        }

        void ExtendedDataGridView_RowLeave(object sender, DataGridViewCellEventArgs e)
        {

            saveCurrentItem();

        }

        public void saveCurrentItem()
        {
            if (IsCurrentRowDirty)
            {
                BindingSource dataBindingSource = (BindingSource)DataSource;

                this.EndEdit();
                string err = validateObject(dataBindingSource.Current);
                if (err != null)
                {
                }
                else
                {
                    object tempObject = Clone(dataBindingSource.Current);
                    err = updateObject(ref tempObject);
                    CopyObject(tempObject, dataBindingSource.Current);
                }
                if (err != null)
                {
                    rowCancel = true;
                    CurrentRow.ErrorText = err;
                }
            }
        }

        protected bool RaiseSaveNeeded(object toSave)
        {
            if (SaveNeeded != null)
            {
                SaveNeededEventArgs args = new SaveNeededEventArgs(toSave);
                SaveNeeded(this, args);
                return args.Success;
            }
            return true;
        }
        protected bool RaiseCreateNeeded(object toSave)
        {
            if (CreateNeeded != null)
            {
                CreateNeededEventArgs args = new CreateNeededEventArgs(toSave);
                CreateNeeded(this, args);
                return args.Success;
            }
            return true;
        }

        public bool IsEqual(object o1, object o2)
        {
            FieldInfo[] fields1 = o1.GetType().GetFields();
            PropertyInfo[] properties1 = o1.GetType().GetProperties();
            FieldInfo[] fields2 = o2.GetType().GetFields();
            PropertyInfo[] properties2 = o2.GetType().GetProperties();

            int i = 0;
            foreach (PropertyInfo p1 in properties1)
            {
                if (p1.GetValue(o1, null) == null && properties2[i].GetValue(o2, null) == null)
                {

                }
                else
                {
                    if (p1.GetValue(o1, null) == null && properties2[i].GetValue(o2, null) != null)
                    {
                        return false;
                    }
                    if (p1.GetValue(o1, null) != null && properties2[i].GetValue(o2, null) == null)
                    {
                        return false;
                    }

                    if (!(p1.GetValue(o1, null).Equals(properties2[i].GetValue(o2, null))))
                    {
                        return false;
                    }
                }
                i++;
            }
            i = 0;
            foreach (FieldInfo f1 in fields1)
            {
                if (!f1.GetValue(o1).Equals(fields2[i].GetValue(o2)))
                {
                    return false;
                }
            }
            return true;
        }

        public object Clone(object toClone)
        {
            //First we create an instance of this specific type.
            object newObject = Activator.CreateInstance(toClone.GetType());
            CopyObject(toClone, newObject);
            return newObject;
        }

        public void CopyObject(object toCopy, object target)
        {
            //We get the array of fields for the new type instance.
            FieldInfo[] fields = target.GetType().GetFields();
            PropertyInfo[] properties = target.GetType().GetProperties();

            int i = 0;
            foreach (PropertyInfo fi in toCopy.GetType().GetProperties())
            {
                //We query if the fiels support the ICloneable interface.
                Type ICloneType = fi.PropertyType.
                            GetInterface("ICloneable", true);

                if (ICloneType != null && fi.GetValue(toCopy, null) != null)
                {
                    //Getting the ICloneable interface from the object.
                    ICloneable IClone = (ICloneable)fi.GetValue(toCopy, null);

                    //We use the clone method to set the new value to the field.
                    properties[i].SetValue(target, IClone.Clone(), null);
                }
                else
                {
                    // If the field doesn't support the ICloneable 
                    // interface then just set it.
                    properties[i].SetValue(target, fi.GetValue(toCopy, null), null);
                }

                //Now we check if the object support the 
                //IEnumerable interface, so if it does
                //we need to enumerate all its items and check if 
                //they support the ICloneable interface.
                Type IEnumerableType = fi.PropertyType.GetInterface
                                ("IEnumerable", true);
                if (IEnumerableType != null)
                {
                    //Get the IEnumerable interface from the field.
                    IEnumerable IEnum = (IEnumerable)fi.GetValue(toCopy, null);

                    //This version support the IList and the 
                    //IDictionary interfaces to iterate on collections.
                    Type IListType = properties[i].PropertyType.GetInterface
                                        ("IList", true);
                    Type IDicType = properties[i].PropertyType.GetInterface
                                        ("IDictionary", true);

                    int j = 0;
                    if (IListType != null)
                    {
                        //Getting the IList interface.
                        IList list = (IList)properties[i].GetValue(target, null);

                        foreach (object obj in IEnum)
                        {
                            //Checking to see if the current item 
                            //support the ICloneable interface.
                            ICloneType = obj.GetType().
                                GetInterface("ICloneable", true);

                            if (ICloneType != null)
                            {
                                //If it does support the ICloneable interface, 
                                //we use it to set the clone of
                                //the object in the list.
                                ICloneable clone = (ICloneable)obj;

                                list[j] = clone.Clone();
                            }

                            //NOTE: If the item in the list is not 
                            //support the ICloneable interface then in the 
                            //cloned list this item will be the same 
                            //item as in the original list
                            //(as long as this type is a reference type).

                            j++;
                        }
                    }
                    else if (IDicType != null)
                    {
                        //Getting the dictionary interface.
                        IDictionary dic = (IDictionary)properties[i].
                                            GetValue(target, null);
                        j = 0;

                        foreach (DictionaryEntry de in IEnum)
                        {
                            //Checking to see if the item 
                            //support the ICloneable interface.
                            ICloneType = de.Value.GetType().
                                GetInterface("ICloneable", true);

                            if (ICloneType != null)
                            {
                                ICloneable clone = (ICloneable)de.Value;

                                dic[de.Key] = clone.Clone();
                            }
                            j++;
                        }
                    }
                }
                i++;
            }

            i = 0;
            foreach (FieldInfo fi in toCopy.GetType().GetFields())
            {
                //We query if the fiels support the ICloneable interface.
                Type ICloneType = fi.FieldType.
                            GetInterface("ICloneable", true);

                if (ICloneType != null)
                {
                    //Getting the ICloneable interface from the object.
                    ICloneable IClone = (ICloneable)fi.GetValue(this);

                    //We use the clone method to set the new value to the field.
                    fields[i].SetValue(target, IClone.Clone());
                }
                else
                {
                    // If the field doesn't support the ICloneable 
                    // interface then just set it.
                    fields[i].SetValue(target, fi.GetValue(this));
                }

                //Now we check if the object support the 
                //IEnumerable interface, so if it does
                //we need to enumerate all its items and check if 
                //they support the ICloneable interface.
                Type IEnumerableType = fi.FieldType.GetInterface
                                ("IEnumerable", true);
                if (IEnumerableType != null)
                {
                    //Get the IEnumerable interface from the field.
                    IEnumerable IEnum = (IEnumerable)fi.GetValue(this);

                    //This version support the IList and the 
                    //IDictionary interfaces to iterate on collections.
                    Type IListType = fields[i].FieldType.GetInterface
                                        ("IList", true);
                    Type IDicType = fields[i].FieldType.GetInterface
                                        ("IDictionary", true);

                    int j = 0;
                    if (IListType != null)
                    {
                        //Getting the IList interface.
                        IList list = (IList)fields[i].GetValue(target);

                        foreach (object obj in IEnum)
                        {
                            //Checking to see if the current item 
                            //support the ICloneable interface.
                            ICloneType = obj.GetType().
                                GetInterface("ICloneable", true);

                            if (ICloneType != null)
                            {
                                //If it does support the ICloneable interface, 
                                //we use it to set the clone of
                                //the object in the list.
                                ICloneable clone = (ICloneable)obj;

                                list[j] = clone.Clone();
                            }

                            //NOTE: If the item in the list is not 
                            //support the ICloneable interface then in the 
                            //cloned list this item will be the same 
                            //item as in the original list
                            //(as long as this type is a reference type).

                            j++;
                        }
                    }
                    else if (IDicType != null)
                    {
                        //Getting the dictionary interface.
                        IDictionary dic = (IDictionary)fields[i].
                                            GetValue(target);
                        j = 0;

                        foreach (DictionaryEntry de in IEnum)
                        {
                            //Checking to see if the item 
                            //support the ICloneable interface.
                            ICloneType = de.Value.GetType().
                                GetInterface("ICloneable", true);

                            if (ICloneType != null)
                            {
                                ICloneable clone = (ICloneable)de.Value;

                                dic[de.Key] = clone.Clone();
                            }
                            j++;
                        }
                    }
                }
                i++;
            }
        }

    }

    public class SaveNeededEventArgs : EventArgs
    {
        private object toSave;
        private bool success;
        private string errorMessage;
        public SaveNeededEventArgs(object toSave)
        {
            this.toSave = toSave;
        }

        public object ToSave
        {
            get
            {
                return toSave;
            }
        }
        public bool Success
        {
            get
            {
                return success;
            }
            set
            {
                success = value;
            }
        }
        public String ErrorMessage
        {
            get
            {
                return errorMessage;
            }
            set
            {
                errorMessage = value;
            }
        }

    }

    public class CreateNeededEventArgs : EventArgs
    {
        private object toCreate;
        private bool success;
        private string errorMessage;
        public CreateNeededEventArgs(object toCreate)
        {
            this.toCreate = toCreate;
        }

        public object ToCreate
        {
            get
            {
                return toCreate;
            }
        }

        public bool Success
        {
            get
            {
                return success;
            }
            set
            {
                success = value;
            }
        }
        public String ErrorMessage
        {
            get
            {
                return errorMessage;
            }
            set
            {
                errorMessage = value;
            }
        }

    }
}
