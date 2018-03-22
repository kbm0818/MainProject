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
    class Shaders
    {
        private ListBox _listBox;
        private TextBox _skyShaderFilePathText;
        private TextBox _terrainShaderFilePathText;

        private readonly string _shaderPath = Path.Combine(Environment.CurrentDirectory, "../../_Shaders/");

        public string ShaderPath
        {
            get { return _shaderPath; }
        }

        public Shaders(ListBox listBox, TextBox skyShaderFilePathText, TextBox terrainShaderFilePathText)
        {
            _listBox = listBox;
            _skyShaderFilePathText = skyShaderFilePathText;
            _terrainShaderFilePathText = terrainShaderFilePathText;

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
            Helper.SearchDirectory(ref fileList, _shaderPath, "*.hlsl");

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

        public void DragEnterInSky(object sender, DragEventArgs e)
        {
            Type type = typeof(FIleItem);
            if(e.Data.GetDataPresent(type))
                e.Effect = DragDropEffects.Copy;
        }

        public void DragDropInSky(object sender, DragEventArgs e)
        {
            Type type = typeof(FIleItem);
            if (e.Data.GetDataPresent(type))
            {
                FIleItem item = (FIleItem)e.Data.GetData(type);

                _skyShaderFilePathText.Text = item.File;

                Cs_SetSkyShader(new StringBuilder(item.Path));
            }
        }

        public void DragEnterInTerrain(object sender, DragEventArgs e)
        {
            Type type = typeof(FIleItem);
            if (e.Data.GetDataPresent(type))
                e.Effect = DragDropEffects.Copy;
        }

        public void DragDropInTerrain(object sender, DragEventArgs e)
        {
            Type type = typeof(FIleItem);
            if (e.Data.GetDataPresent(type))
            {
                FIleItem item = (FIleItem)e.Data.GetData(type);

                _terrainShaderFilePathText.Text = item.File;

                Cs_SetTerrainShader(new StringBuilder(item.Path));
            }
        }

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetSkyShader(StringBuilder str);

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainShader(StringBuilder str);
    }
}
