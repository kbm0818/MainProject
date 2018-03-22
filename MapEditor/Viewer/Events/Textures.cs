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
    class Textures
    {
        private ListBox _listBox;
        private TextBox _TerrainDiffuseFileText;
        private TextBox _TerrainStage1FileText;
        private TextBox _TerrainStage2FileText;
        private TextBox _TerrainStage3FileText;
        private TextBox _TerrainStage4FileText;

        private readonly string _texturePath = Path.Combine(Environment.CurrentDirectory, "../../_Contents/Textures/");

        public string TexturePath
        {
            get { return _texturePath; }
        }

        public Textures(ListBox listBox, TextBox terrainDiffuseFileText, TextBox terrainStage1FileText, TextBox terrainStage2FileText, TextBox terrainStage3FileText, TextBox terrainStage4FileText)
        {
            _listBox = listBox;
            _TerrainDiffuseFileText = terrainDiffuseFileText;
            _TerrainStage1FileText = terrainStage1FileText;
            _TerrainStage2FileText = terrainStage2FileText;
            _TerrainStage3FileText = terrainStage3FileText;
            _TerrainStage4FileText = terrainStage4FileText;
            
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
            Helper.SearchDirectory(ref fileList, _texturePath, "*.png");

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
            Type type = typeof(FIleItem);
            if (e.Data.GetDataPresent(type))
                e.Effect = DragDropEffects.Copy;
        }

        public void DragDropInTerrainDiffuseFileText(object sender, DragEventArgs e)
        {
            Type type = typeof(FIleItem);
            if (e.Data.GetDataPresent(type))
            {
                FIleItem item = (FIleItem)e.Data.GetData(type);

                _TerrainDiffuseFileText.Text = item.File;

                Cs_SetTerrainDiffuseFile(new StringBuilder(item.Path));
            }
        }

        public void DragDropInTerrainStage1FileText(object sender, DragEventArgs e)
        {
            Type type = typeof(FIleItem);
            if (e.Data.GetDataPresent(type))
            {
                FIleItem item = (FIleItem)e.Data.GetData(type);

                _TerrainStage1FileText.Text = item.File;

                Cs_SetTerrainStage1File(new StringBuilder(item.Path));
            }
        }

        public void DragDropInTerrainStage2FileText(object sender, DragEventArgs e)
        {
            Type type = typeof(FIleItem);
            if (e.Data.GetDataPresent(type))
            {
                FIleItem item = (FIleItem)e.Data.GetData(type);

                _TerrainStage2FileText.Text = item.File;

                Cs_SetTerrainStage2File(new StringBuilder(item.Path));
            }
        }

        public void DragDropInTerrainStage3FileText(object sender, DragEventArgs e)
        {
            Type type = typeof(FIleItem);
            if (e.Data.GetDataPresent(type))
            {
                FIleItem item = (FIleItem)e.Data.GetData(type);

                _TerrainStage3FileText.Text = item.File;

                Cs_SetTerrainStage3File(new StringBuilder(item.Path));
            }
        }

        public void DragDropInTerrainStage4FileText(object sender, DragEventArgs e)
        {
            Type type = typeof(FIleItem);
            if (e.Data.GetDataPresent(type))
            {
                FIleItem item = (FIleItem)e.Data.GetData(type);

                _TerrainStage4FileText.Text = item.File;

                Cs_SetTerrainStage4File(new StringBuilder(item.Path));
            }
        }

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainDiffuseFile(StringBuilder str);
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainStage1File(StringBuilder str);
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainStage2File(StringBuilder str);
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainStage3File(StringBuilder str);
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainStage4File(StringBuilder str);
    }
}
