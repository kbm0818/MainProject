using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Viewer
{
    public partial class MainForm : Form
    {
        private Shaders _shaders;
        private Textures _textures;
        private Models _models;
        
        public MainForm()
        {
            InitializeComponent();

            LogView.ListView = this.LogListView;
            Connect.RenderBox = this.RenderBox;
            this.Load += Connect.Create;
            this.Load += DataLoad;

            this.FormClosed += Connect.Destroy;

            Application.Idle += Connect.Idle;


            this.RenderBox.MouseEnter += Connect.MouseEnter;
            this.RenderBox.MouseLeave += Connect.MouseLeave;
            this.RenderBox.AllowDrop = true;

            /////////////////// Shaders /////////////////////
            _shaders = new Shaders(ShaderFileList, SkyShaderFilePathText, TerrainShaderFilePathText);
            RefreshShaderFileList.Click += _shaders.Refresh;

            ShaderFileList.MouseDown += ShaderFileList_MouseDown;

            SkyShaderFilePathText.DragEnter += _shaders.DragEnterInSky;
            SkyShaderFilePathText.DragDrop += _shaders.DragDropInSky;

            TerrainShaderFilePathText.DragEnter += _shaders.DragDropInTerrain;
            TerrainShaderFilePathText.DragDrop += _shaders.DragDropInTerrain;
            /////////////////// Shaders End /////////////////////

            /////////////////// Textures /////////////////////
            _textures = new Textures(TextureFileList, TerrainDiffuseFileText, TerrainStage1FileText, TerrainStage2FileText, TerrainStage3FileText, TerrainStage4FileText);
            RefreshTextureFileList.Click += _textures.Refresh;

            TextureFileList.MouseDown += TextureFileList_MouseDown;

            TerrainDiffuseFileText.DragEnter += _textures.DragEnter;
            TerrainStage1FileText.DragEnter += _textures.DragEnter;
            TerrainStage2FileText.DragEnter += _textures.DragEnter;
            TerrainStage3FileText.DragEnter += _textures.DragEnter;
            TerrainStage4FileText.DragEnter += _textures.DragEnter;

            TerrainDiffuseFileText.DragDrop += _textures.DragDropInTerrainDiffuseFileText;
            TerrainStage1FileText.DragDrop += _textures.DragDropInTerrainStage1FileText;
            TerrainStage2FileText.DragDrop += _textures.DragDropInTerrainStage2FileText;
            TerrainStage3FileText.DragDrop += _textures.DragDropInTerrainStage3FileText;
            TerrainStage4FileText.DragDrop += _textures.DragDropInTerrainStage4FileText;

            /////////////////// Textures End /////////////////////

            /////////////////// Models  /////////////////////
            _models = new Models(ModelFileList,ModelTXText, ModelTYText, ModelTZText, ModelRXText, ModelRYText, ModelRZText, ModelSXText, ModelSYText, ModelSZText);
            ModelFileList.MouseDown += ModelFileList_MouseDown;

            RenderBox.DragEnter += _models.DragEnter;
            RenderBox.DragDrop += _models.DragDrop_InRenderBox;
           
            RefreshModelFileList.Click += _models.Refresh;

            /////////////////// Models End /////////////////////

            FileOpenMenu.Click += FileOpenMenu_Click;

            TerrainWidthText.KeyPress += textBox_KeyPress;
            TerrainHeightText.KeyPress += textBox_KeyPress;
            TerrainBrushSizeText.KeyPress += textBox_KeyPress;
            TerrainHeightOptionValueText.KeyPress += textBox_KeyPress;

            TerrainSizeChangeButton.Click += TerrainSizeChangeButton_Clicked;

            TerrainDiffuseColorChangeButton.Click += TerrainDiffuseColorChangeButton_Click;
            TerrainAmbientColorChangeButton.Click += TerrainAmbientColorChangeButton_Click;

            TerrainHeightRadioButton.CheckedChanged += TerrainHeightRadioButton_CkeckedChanged;
            TerrainSplattingRadioButton.CheckedChanged += TerrainSplattingRadioButton_CkeckedChanged;

            TerrainHeightRadioButton.CheckedChanged += TerrainHeightRadioButton_CheckedChanged;
            TerrainSplattingRadioButton.CheckedChanged += TerrainSplattingRadioButton_CheckedChanged;

            TerrainSplattingStage1RadioButton.CheckedChanged += TerrainSplattingStage1RadioButton_CheckChanged;
            TerrainSplattingStage2RadioButton.CheckedChanged += TerrainSplattingStage2RadioButton_CheckChanged;
            TerrainSplattingStage3RadioButton.CheckedChanged += TerrainSplattingStage3RadioButton_CheckChanged;
            TerrainSplattingStage4RadioButton.CheckedChanged += TerrainSplattingStage4RadioButton_CheckChanged;

            TerrainHeightOptionNoneRadioButton.CheckedChanged += TerrainHeightOptionNoneRadioButton_CheckChanged;
            TerrainHeightOptionHeightLockRadioButton.CheckedChanged += TerrainHeightOptionHeightLockRadioButton_CheckChanged;
            TerrainHeightOptionValueText.TextChanged += TerrainHeightOptionValueText_TextChanged;

            TerrainBrushSizeText.TextChanged += TerrainBrushSizeText_TextChanged;
            TerrainBushTypeRectRadioButton.CheckedChanged += TerrainBushTypeRectRadioButton_CheckedChanged;
            TerrainBushTypeCircleRadioButton.CheckedChanged += TerrainBushTypeCircleRadioButton_CheckChanged;

            SkyApexColorButton.Click += SkyApexColorButton_Click;
            SkyCenterColorButton.Click += SkyCenterColorButton_Click;

            ConvertFbxFile.Click += ConvertFbxFile_Click;
        }

        private void ConvertFbxFile_Click(object sender, EventArgs e)
        {
            using (FolderBrowserDialog folderDlg = new FolderBrowserDialog())
            {
                DirectoryInfo info = new DirectoryInfo(@"c:\\Users\Me\Documents\Visual Studio 2015\Projects\_Contents\Models");
                folderDlg.SelectedPath = info.FullName;
                if (folderDlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    MessageBox.Show("선택한 폴더: " + folderDlg.SelectedPath);
                }
            }
        }

        private void SkyApexColorButton_Click(object sender, System.EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {
                SkyApexColorButton.BackColor = colorDialog1.Color;

                Cs_SetSkyApexColor(colorDialog1.Color.ToArgb());
            }
        }

        private void SkyCenterColorButton_Click(object sender, System.EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {
                SkyCenterColorButton.BackColor = colorDialog1.Color;

                Cs_SetSkyCenterColor(colorDialog1.Color.ToArgb());
            }
        }

        private void TerrainBushTypeRectRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            if (TerrainBushTypeRectRadioButton.Checked)
                Cs_SetTerrainBrushShape(0);
        }
      
        private void TerrainBushTypeCircleRadioButton_CheckChanged(object sender, EventArgs e)
        {
            if (TerrainBushTypeCircleRadioButton.Checked)
                Cs_SetTerrainBrushShape(1);
        }

        private void TerrainBrushSizeText_TextChanged(object sender, EventArgs e)
        {
            int value;
            bool parsed = Int32.TryParse(TerrainBrushSizeText.Text, out value);
            if(parsed)
                Cs_SetTerrainBrushSize(value);
        }
        private void TerrainHeightOptionValueText_TextChanged(object sender, EventArgs e)
        {
            int value;
            bool parsed = Int32.TryParse(TerrainHeightOptionValueText.Text, out value);
            if (parsed)
                Cs_SetTerrainBrushValue(value);
        }
        private void TerrainHeightOptionHeightLockRadioButton_CheckChanged(object sender, EventArgs e)
        {
            if (TerrainHeightOptionHeightLockRadioButton.Checked)
                Cs_SetBrushHeightLock(true);
        }
        private void TerrainHeightOptionNoneRadioButton_CheckChanged(object sender, EventArgs e)
        {
            if (TerrainHeightOptionNoneRadioButton.Checked)
                Cs_SetBrushHeightLock(false);
        }
        private void TerrainSplattingStage4RadioButton_CheckChanged(object sender, EventArgs e)
        {
            if (TerrainSplattingStage4RadioButton.Checked)
                Cs_SetTerrainBrushSplattingImage(3);
        }
        private void TerrainSplattingStage3RadioButton_CheckChanged(object sender, EventArgs e)
        {
            if (TerrainSplattingStage3RadioButton.Checked)
                Cs_SetTerrainBrushSplattingImage(2);
        }
        private void TerrainSplattingStage2RadioButton_CheckChanged(object sender, EventArgs e)
        {
            if (TerrainSplattingStage2RadioButton.Checked)
                Cs_SetTerrainBrushSplattingImage(1);
        }
        private void TerrainSplattingStage1RadioButton_CheckChanged(object sender, EventArgs e)
        {
            if (TerrainSplattingStage1RadioButton.Checked)
                Cs_SetTerrainBrushSplattingImage(0);
        }
        private void TerrainHeightRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            if(TerrainHeightRadioButton.Checked)
                Cs_SetTerrainBrushType(0);
        }
  
        private void TerrainSplattingRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            if (TerrainSplattingRadioButton.Checked)
                Cs_SetTerrainBrushType(1);
        }

        private void TerrainHeightRadioButton_CkeckedChanged(object sender, EventArgs e)
        {
            if(TerrainHeightRadioButton.Checked)
            {
                TerrainBrushHeightGroupBox.Visible = true;
                TerrainBrushHeightOptionGroupBox.Visible = true;
                TerrainBrushSplattingGroupBox.Visible = false;
                TerrainBrushSpattingOptionGroupBox.Visible = false;

                Cs_SetTerrainBrushType(0);
            }
        }

        private void TerrainSplattingRadioButton_CkeckedChanged(object sender, EventArgs e)
        {
            if(TerrainSplattingRadioButton.Checked)
            {
                TerrainBrushSplattingGroupBox.Visible = true;
                TerrainBrushSpattingOptionGroupBox.Visible = true;
                TerrainBrushHeightGroupBox.Visible = false;
                TerrainBrushHeightOptionGroupBox.Visible = false;

                Cs_SetTerrainBrushType(1);
            }
        }

        private void TerrainDiffuseColorChangeButton_Click(object sender, System.EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {
                TerrainDiffuseColorChangeButton.BackColor = colorDialog1.Color;
            
                Cs_SetTerrainDiffuseColor(colorDialog1.Color.ToArgb());
            }
        }

        private void TerrainAmbientColorChangeButton_Click(object sender, System.EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {
                TerrainAmbientColorChangeButton.BackColor = colorDialog1.Color;
           
                Cs_SetTerrainAmbientColor(colorDialog1.Color.ToArgb());
            }
        }

        private void textBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && (e.KeyChar != '.'))
            {
                e.Handled = true;
            }

            // only allow one decimal point
            if ((e.KeyChar == '.') && ((sender as TextBox).Text.IndexOf('.') > -1))
            {
                e.Handled = true;
            }
        }
        private void TerrainSizeChangeButton_Clicked(object sender, EventArgs e)
        {
            uint value, value2;
            bool parsed = UInt32.TryParse(TerrainWidthText.Text, out value);
            parsed &= UInt32.TryParse(TerrainHeightText.Text, out value2);
            if (parsed)
                Cs_SetTerrainSize(value, value2);
        }
        
        private void TerrainWidthText_TextChanged(object sender, EventArgs e)
        {
            uint value;
            bool parsed = UInt32.TryParse(TerrainWidthText.Text, out value);
           
            if (parsed)
                Cs_SetTerrainWidth(value);
        }

        private void TerrainHeightText_TextChanged(object sender, EventArgs e)
        {
            uint value;
            bool parsed = UInt32.TryParse(TerrainHeightText.Text, out value);

            if (parsed)
                Cs_SetTerrainWidth(value);
        }

        private void FileOpenMenu_Click(object sender, EventArgs e)
        {
            MessageBox.Show("파일 열기");
        }

        private void ShaderFileList_MouseDown(object sender, MouseEventArgs e)
        {
            if (ShaderFileList.SelectedItem == null)
                return;

            Shaders.FIleItem item = (Shaders.FIleItem)ShaderFileList.SelectedItem;

            DoDragDrop(item, DragDropEffects.Copy);
        }

        private void TextureFileList_MouseDown(object sender, MouseEventArgs e)
        {
            if (TextureFileList.SelectedItem == null)
                return;

            Textures.FIleItem item = (Textures.FIleItem)TextureFileList.SelectedItem;

            DoDragDrop(item, DragDropEffects.Copy);
        }

        private void ModelFileList_MouseDown(object sender, MouseEventArgs e)
        {
            if (ModelFileList.SelectedItem == null)
                return;

            Models.FIleItem item = (Models.FIleItem)ModelFileList.SelectedItem;
    
            DoDragDrop(item, DragDropEffects.Copy);
        }

        public void DataLoad(object sender, EventArgs e)
        {
            TerrainWidthText.Text = Cs_GetTerrainWidth().ToString();
            TerrainHeightText.Text = Cs_GetTerrainHeight().ToString();
        
            TerrainDiffuseColorChangeButton.BackColor = Color.FromArgb((int)Cs_GetTerrainDiffuseColor());
            TerrainAmbientColorChangeButton.BackColor = Color.FromArgb((int)Cs_GetTerrainAmbientColor());

            if(Cs_GetTerrainBrushType() == 0)
                TerrainHeightRadioButton.Checked = true;
            else
                TerrainSplattingRadioButton.Checked = true;

            if (Cs_GetTerrainBrushShape() == 0)
                TerrainBushTypeRectRadioButton.Checked = true;
            else
                TerrainBushTypeCircleRadioButton.Checked = true;

            int temp = Cs_GetTerrainBrushSplattingImage();

            switch(temp)
            {
                case 0:
                TerrainSplattingStage1RadioButton.Checked = true;
                break;
                case 1:
                TerrainSplattingStage2RadioButton.Checked = true;
                break;
                case 2:
                TerrainSplattingStage3RadioButton.Checked = true;
                break;
                case 3:
                TerrainSplattingStage4RadioButton.Checked = true;
                break;
            }

            TerrainHeightOptionValueText.Text = Cs_GetTerrainBrushValue().ToString();

            TerrainBrushSizeText.Text = Cs_GetTerrainBrushSize().ToString();

            if (Cs_GetBrushHeightLock() == true)
                TerrainHeightOptionHeightLockRadioButton.Checked = true;
            else
                TerrainHeightOptionNoneRadioButton.Checked = true;
        }

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Cs_GetTerrainWidth();
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Cs_GetTerrainHeight();

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainWidth(uint width);
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainHeight(uint height);
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainSize(uint width, uint height);

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Cs_GetTerrainDiffuseColor();
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Cs_GetTerrainAmbientColor();

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainDiffuseColor(int diffuse);
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainAmbientColor(int ambient);

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Cs_GetTerrainBrushType();
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainBrushType(int type);

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Cs_GetTerrainBrushShape();
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainBrushShape(int type);

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Cs_GetTerrainBrushSplattingImage();
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainBrushSplattingImage(int type);

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern float Cs_GetTerrainBrushSize();
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainBrushSize(float size);

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern float Cs_GetTerrainBrushValue();
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetTerrainBrushValue(float value);

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private static extern bool  Cs_GetBrushHeightLock();
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetBrushHeightLock(bool value);

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetSkyApexColor(int value);
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_SetSkyCenterColor(int value);

    }
}
