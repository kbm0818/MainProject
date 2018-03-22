using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Viewer
{
    class Models
    {
        private ListBox _listBox;
        private TextBox _tx;
        private TextBox _ty;
        private TextBox _tz;
        private TextBox _rx;
        private TextBox _ry;
        private TextBox _rz;
        private TextBox _sx;
        private TextBox _sy;
        private TextBox _sz;


        private readonly string _modelsPath = Path.Combine(Environment.CurrentDirectory, "../../_Contents/Models/");

        public string TexturePath
        {
            get { return _modelsPath; }
        }

        public Models(ListBox listBox, TextBox tx, TextBox ty, TextBox tz, TextBox rx, TextBox ry, TextBox rz, TextBox sx, TextBox sy, TextBox sz)
        {
            _listBox = listBox;
            _tx = tx;
            _ty = ty;
            _tz = tz;
            _rx = rx;
            _ry = ry;
            _rz = rz;
            _sx = sx;
            _sy = sy;
            _sz = sz;
            
            RefreshList();
        }

        public struct FIleItem
        {
            public string File;
            public string Path;

            public override string ToString()
            {
                return File;
            }
        }

        private void RefreshList()
        {
            List<string> fileList = new List<string>();
            Helper.SearchDirectory(ref fileList, _modelsPath, "*.fbx");

            _listBox.Items.Clear();
            foreach (string temp in fileList)
            {
                FIleItem item = new FIleItem();
                item.File = Path.GetFileName(temp);
                item.Path = Path.GetFullPath(temp);

                _listBox.Items.Add(item);
            }

        }

        public void Refresh(object sender, EventArgs e)
        {
            RefreshList();
        }

        public void DragEnter(object sender, DragEventArgs e)
        {
            Connect.Cs_SetFocus(true);
            Type type = typeof(FIleItem);
            if (e.Data.GetDataPresent(type))
                e.Effect = DragDropEffects.Copy;
        }

        public void DragDrop(object sender, DragEventArgs e)
        {
            Type type = typeof(FIleItem);
            if (e.Data.GetDataPresent(type))
            {
                FIleItem item = (FIleItem)e.Data.GetData(type);

                Cs_SetShader(new StringBuilder(item.Path));
            }
        }

        public void DragDrop_InRenderBox(object sender, DragEventArgs e)
        {
            Type type = typeof(FIleItem);
            if (e.Data.GetDataPresent(type))
            {
                FIleItem item = (FIleItem)e.Data.GetData(type);
                System.Drawing.Point temp = Cursor.Position;
                int result = Cs_AddModels(temp.X, temp.Y, new StringBuilder(item.Path));

                //TODO: 모델인포 받았으니 갱신해라
                StringBuilder strtemp = Cs_GetString();
                _tx.Text = strtemp.ToString();

                // _tx.Text = modelInfo.translate.x.ToString();
                //  _ty.Text = modelInfo.translate.y.ToString();
                // _tz.Text = modelInfo.translate.z.ToString();

                //  _rx.Text = modelInfo.rotate.x.ToString();
                // _ry.Text = modelInfo.rotate.y.ToString();
                // _rz.Text = modelInfo.rotate.z.ToString();

                // _sx.Text = modelInfo.scale.x.ToString();
                // _sy.Text = modelInfo.scale.y.ToString();
                // _sz.Text = modelInfo.scale.z.ToString();

            }
        }

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetShader(StringBuilder str);

       // [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
      //  private static extern Cs_GetModelInfo(int index, Connect.ModelInfo info);

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Cs_GetModelsSize();

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Cs_AddModels(int px, int py, StringBuilder str);

        [DllImport("Direct3D.dll")]
        private static extern int Cs_GetModelName(int index, StringBuilder str);

        [DllImport("Direct3D.dll")]
        private static extern StringBuilder Cs_GetString();

    }
}
