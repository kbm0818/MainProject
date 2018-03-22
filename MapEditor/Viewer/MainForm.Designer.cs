namespace Viewer
{
    partial class MainForm
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.RightPanel = new System.Windows.Forms.Panel();
            this.RightSplitContainer = new System.Windows.Forms.SplitContainer();
            this.InpectorTab = new System.Windows.Forms.TabControl();
            this.SkyTab = new System.Windows.Forms.TabPage();
            this.SkyApexColorButton = new System.Windows.Forms.Button();
            this.llll = new System.Windows.Forms.Label();
            this.SkyCenterColorButton = new System.Windows.Forms.Button();
            this.lll = new System.Windows.Forms.Label();
            this.SkyShaderFilePathText = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.TerrainTab = new System.Windows.Forms.TabPage();
            this.TerrainBrushSizeText = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.TerrainBrushOptionPanel = new System.Windows.Forms.Panel();
            this.TerrainBrushSpattingOptionGroupBox = new System.Windows.Forms.GroupBox();
            this.TerrainBrushHeightOptionGroupBox = new System.Windows.Forms.GroupBox();
            this.label12 = new System.Windows.Forms.Label();
            this.TerrainHeightOptionValueText = new System.Windows.Forms.TextBox();
            this.TerrainHeightOptionHeightLockRadioButton = new System.Windows.Forms.RadioButton();
            this.TerrainHeightOptionNoneRadioButton = new System.Windows.Forms.RadioButton();
            this.testPanel1 = new System.Windows.Forms.Panel();
            this.TerrainBrushSplattingGroupBox = new System.Windows.Forms.GroupBox();
            this.TerrainSplattingStage4RadioButton = new System.Windows.Forms.RadioButton();
            this.TerrainSplattingStage2RadioButton = new System.Windows.Forms.RadioButton();
            this.TerrainSplattingStage3RadioButton = new System.Windows.Forms.RadioButton();
            this.TerrainSplattingStage1RadioButton = new System.Windows.Forms.RadioButton();
            this.TerrainBrushHeightGroupBox = new System.Windows.Forms.GroupBox();
            this.TerrainBushTypeCircleRadioButton = new System.Windows.Forms.RadioButton();
            this.TerrainBushTypeRectRadioButton = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.TerrainSplattingRadioButton = new System.Windows.Forms.RadioButton();
            this.TerrainHeightRadioButton = new System.Windows.Forms.RadioButton();
            this.TerrainStage4FileText = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.TerrainStage3FileText = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.TerrainStage2FileText = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.TerrainStage1FileText = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.TerrainDiffuseFileText = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.TerrainAmbientColorChangeButton = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.TerrainDiffuseColorChangeButton = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.TerrainSizeChangeButton = new System.Windows.Forms.Button();
            this.TerrainHeightText = new System.Windows.Forms.TextBox();
            this.TerrainWidthText = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.TerrainShaderFilePathText = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.ModelTab = new System.Windows.Forms.TabPage();
            this.ModelTextureFileText = new System.Windows.Forms.TextBox();
            this.ModelDiffuseFileText = new System.Windows.Forms.TextBox();
            this.ModelShaderFileText = new System.Windows.Forms.TextBox();
            this.label20 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.ModelSZText = new System.Windows.Forms.TextBox();
            this.ModelSYText = new System.Windows.Forms.TextBox();
            this.ModelSXText = new System.Windows.Forms.TextBox();
            this.ModelRZText = new System.Windows.Forms.TextBox();
            this.ModelRYText = new System.Windows.Forms.TextBox();
            this.ModelRXText = new System.Windows.Forms.TextBox();
            this.ModelTZText = new System.Windows.Forms.TextBox();
            this.ModelTYText = new System.Windows.Forms.TextBox();
            this.ModelTXText = new System.Windows.Forms.TextBox();
            this.label17 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.ModelModelNameText = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.RightSplitter = new System.Windows.Forms.Splitter();
            this.ProjectTab = new System.Windows.Forms.TabControl();
            this.ShaderTab = new System.Windows.Forms.TabPage();
            this.RefreshShaderFileList = new System.Windows.Forms.Button();
            this.ShaderFileList = new System.Windows.Forms.ListBox();
            this.TerrainTap = new System.Windows.Forms.TabPage();
            this.RefreshTextureFileList = new System.Windows.Forms.Button();
            this.TextureFileList = new System.Windows.Forms.ListBox();
            this.ModelFileTab = new System.Windows.Forms.TabPage();
            this.RefreshModelFileList = new System.Windows.Forms.Button();
            this.ModelFileList = new System.Windows.Forms.ListBox();
            this.BottomPanel = new System.Windows.Forms.Panel();
            this.LogListView = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.MainPanel = new System.Windows.Forms.Panel();
            this.RenderBox = new System.Windows.Forms.PictureBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.FileMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.FileOpenMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.FileSaveMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.FileExitMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.fbx변환ConverterToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ConvertFbxFile = new System.Windows.Forms.ToolStripMenuItem();
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.RightPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.RightSplitContainer)).BeginInit();
            this.RightSplitContainer.Panel1.SuspendLayout();
            this.RightSplitContainer.Panel2.SuspendLayout();
            this.RightSplitContainer.SuspendLayout();
            this.InpectorTab.SuspendLayout();
            this.SkyTab.SuspendLayout();
            this.TerrainTab.SuspendLayout();
            this.TerrainBrushOptionPanel.SuspendLayout();
            this.TerrainBrushHeightOptionGroupBox.SuspendLayout();
            this.testPanel1.SuspendLayout();
            this.TerrainBrushSplattingGroupBox.SuspendLayout();
            this.TerrainBrushHeightGroupBox.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.ModelTab.SuspendLayout();
            this.ProjectTab.SuspendLayout();
            this.ShaderTab.SuspendLayout();
            this.TerrainTap.SuspendLayout();
            this.ModelFileTab.SuspendLayout();
            this.BottomPanel.SuspendLayout();
            this.MainPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.RenderBox)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // RightPanel
            // 
            this.RightPanel.Controls.Add(this.RightSplitContainer);
            this.RightPanel.Dock = System.Windows.Forms.DockStyle.Right;
            this.RightPanel.Location = new System.Drawing.Point(801, 0);
            this.RightPanel.Margin = new System.Windows.Forms.Padding(1);
            this.RightPanel.Name = "RightPanel";
            this.RightPanel.Size = new System.Drawing.Size(276, 623);
            this.RightPanel.TabIndex = 0;
            // 
            // RightSplitContainer
            // 
            this.RightSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.RightSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.RightSplitContainer.Margin = new System.Windows.Forms.Padding(1);
            this.RightSplitContainer.Name = "RightSplitContainer";
            this.RightSplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // RightSplitContainer.Panel1
            // 
            this.RightSplitContainer.Panel1.Controls.Add(this.InpectorTab);
            this.RightSplitContainer.Panel1.Controls.Add(this.RightSplitter);
            // 
            // RightSplitContainer.Panel2
            // 
            this.RightSplitContainer.Panel2.Controls.Add(this.ProjectTab);
            this.RightSplitContainer.Size = new System.Drawing.Size(276, 623);
            this.RightSplitContainer.SplitterDistance = 349;
            this.RightSplitContainer.SplitterWidth = 2;
            this.RightSplitContainer.TabIndex = 0;
            // 
            // InpectorTab
            // 
            this.InpectorTab.Controls.Add(this.SkyTab);
            this.InpectorTab.Controls.Add(this.TerrainTab);
            this.InpectorTab.Controls.Add(this.ModelTab);
            this.InpectorTab.Dock = System.Windows.Forms.DockStyle.Fill;
            this.InpectorTab.Location = new System.Drawing.Point(0, 0);
            this.InpectorTab.Margin = new System.Windows.Forms.Padding(1);
            this.InpectorTab.Name = "InpectorTab";
            this.InpectorTab.SelectedIndex = 0;
            this.InpectorTab.Size = new System.Drawing.Size(276, 339);
            this.InpectorTab.TabIndex = 1;
            // 
            // SkyTab
            // 
            this.SkyTab.Controls.Add(this.SkyApexColorButton);
            this.SkyTab.Controls.Add(this.llll);
            this.SkyTab.Controls.Add(this.SkyCenterColorButton);
            this.SkyTab.Controls.Add(this.lll);
            this.SkyTab.Controls.Add(this.SkyShaderFilePathText);
            this.SkyTab.Controls.Add(this.label1);
            this.SkyTab.Location = new System.Drawing.Point(4, 22);
            this.SkyTab.Margin = new System.Windows.Forms.Padding(1);
            this.SkyTab.Name = "SkyTab";
            this.SkyTab.Padding = new System.Windows.Forms.Padding(1);
            this.SkyTab.Size = new System.Drawing.Size(268, 313);
            this.SkyTab.TabIndex = 0;
            this.SkyTab.Text = "Sky";
            this.SkyTab.UseVisualStyleBackColor = true;
            // 
            // SkyApexColorButton
            // 
            this.SkyApexColorButton.Location = new System.Drawing.Point(83, 75);
            this.SkyApexColorButton.Name = "SkyApexColorButton";
            this.SkyApexColorButton.Size = new System.Drawing.Size(22, 23);
            this.SkyApexColorButton.TabIndex = 16;
            this.SkyApexColorButton.UseVisualStyleBackColor = true;
            // 
            // llll
            // 
            this.llll.AutoSize = true;
            this.llll.Location = new System.Drawing.Point(31, 80);
            this.llll.Name = "llll";
            this.llll.Size = new System.Drawing.Size(34, 12);
            this.llll.TabIndex = 15;
            this.llll.Text = "Apex";
            // 
            // SkyCenterColorButton
            // 
            this.SkyCenterColorButton.Location = new System.Drawing.Point(83, 46);
            this.SkyCenterColorButton.Name = "SkyCenterColorButton";
            this.SkyCenterColorButton.Size = new System.Drawing.Size(22, 23);
            this.SkyCenterColorButton.TabIndex = 14;
            this.SkyCenterColorButton.UseVisualStyleBackColor = true;
            // 
            // lll
            // 
            this.lll.AutoSize = true;
            this.lll.Location = new System.Drawing.Point(23, 51);
            this.lll.Name = "lll";
            this.lll.Size = new System.Drawing.Size(42, 12);
            this.lll.TabIndex = 13;
            this.lll.Text = "Center";
            // 
            // SkyShaderFilePathText
            // 
            this.SkyShaderFilePathText.AllowDrop = true;
            this.SkyShaderFilePathText.Location = new System.Drawing.Point(98, 4);
            this.SkyShaderFilePathText.Margin = new System.Windows.Forms.Padding(1);
            this.SkyShaderFilePathText.Name = "SkyShaderFilePathText";
            this.SkyShaderFilePathText.Size = new System.Drawing.Size(170, 21);
            this.SkyShaderFilePathText.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 9);
            this.label1.Margin = new System.Windows.Forms.Padding(1, 0, 1, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(90, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "ShaderFilePath";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // TerrainTab
            // 
            this.TerrainTab.Controls.Add(this.TerrainBrushSizeText);
            this.TerrainTab.Controls.Add(this.label14);
            this.TerrainTab.Controls.Add(this.TerrainBrushOptionPanel);
            this.TerrainTab.Controls.Add(this.testPanel1);
            this.TerrainTab.Controls.Add(this.groupBox1);
            this.TerrainTab.Controls.Add(this.TerrainStage4FileText);
            this.TerrainTab.Controls.Add(this.label13);
            this.TerrainTab.Controls.Add(this.TerrainStage3FileText);
            this.TerrainTab.Controls.Add(this.label10);
            this.TerrainTab.Controls.Add(this.TerrainStage2FileText);
            this.TerrainTab.Controls.Add(this.label11);
            this.TerrainTab.Controls.Add(this.TerrainStage1FileText);
            this.TerrainTab.Controls.Add(this.label9);
            this.TerrainTab.Controls.Add(this.TerrainDiffuseFileText);
            this.TerrainTab.Controls.Add(this.label8);
            this.TerrainTab.Controls.Add(this.TerrainAmbientColorChangeButton);
            this.TerrainTab.Controls.Add(this.label7);
            this.TerrainTab.Controls.Add(this.TerrainDiffuseColorChangeButton);
            this.TerrainTab.Controls.Add(this.label6);
            this.TerrainTab.Controls.Add(this.TerrainSizeChangeButton);
            this.TerrainTab.Controls.Add(this.TerrainHeightText);
            this.TerrainTab.Controls.Add(this.TerrainWidthText);
            this.TerrainTab.Controls.Add(this.label5);
            this.TerrainTab.Controls.Add(this.label4);
            this.TerrainTab.Controls.Add(this.TerrainShaderFilePathText);
            this.TerrainTab.Controls.Add(this.label2);
            this.TerrainTab.Location = new System.Drawing.Point(4, 22);
            this.TerrainTab.Name = "TerrainTab";
            this.TerrainTab.Size = new System.Drawing.Size(268, 313);
            this.TerrainTab.TabIndex = 1;
            this.TerrainTab.Text = "Terrain";
            this.TerrainTab.UseVisualStyleBackColor = true;
            // 
            // TerrainBrushSizeText
            // 
            this.TerrainBrushSizeText.AllowDrop = true;
            this.TerrainBrushSizeText.Location = new System.Drawing.Point(201, 126);
            this.TerrainBrushSizeText.Margin = new System.Windows.Forms.Padding(1);
            this.TerrainBrushSizeText.Name = "TerrainBrushSizeText";
            this.TerrainBrushSizeText.Size = new System.Drawing.Size(61, 21);
            this.TerrainBrushSizeText.TabIndex = 30;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(135, 131);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(63, 12);
            this.label14.TabIndex = 29;
            this.label14.Text = "BrushSize";
            // 
            // TerrainBrushOptionPanel
            // 
            this.TerrainBrushOptionPanel.Controls.Add(this.TerrainBrushSpattingOptionGroupBox);
            this.TerrainBrushOptionPanel.Controls.Add(this.TerrainBrushHeightOptionGroupBox);
            this.TerrainBrushOptionPanel.Location = new System.Drawing.Point(6, 228);
            this.TerrainBrushOptionPanel.Name = "TerrainBrushOptionPanel";
            this.TerrainBrushOptionPanel.Size = new System.Drawing.Size(256, 85);
            this.TerrainBrushOptionPanel.TabIndex = 28;
            // 
            // TerrainBrushSpattingOptionGroupBox
            // 
            this.TerrainBrushSpattingOptionGroupBox.Location = new System.Drawing.Point(0, 0);
            this.TerrainBrushSpattingOptionGroupBox.Name = "TerrainBrushSpattingOptionGroupBox";
            this.TerrainBrushSpattingOptionGroupBox.Size = new System.Drawing.Size(256, 85);
            this.TerrainBrushSpattingOptionGroupBox.TabIndex = 3;
            this.TerrainBrushSpattingOptionGroupBox.TabStop = false;
            this.TerrainBrushSpattingOptionGroupBox.Text = "SplattingOption";
            this.TerrainBrushSpattingOptionGroupBox.Visible = false;
            // 
            // TerrainBrushHeightOptionGroupBox
            // 
            this.TerrainBrushHeightOptionGroupBox.Controls.Add(this.label12);
            this.TerrainBrushHeightOptionGroupBox.Controls.Add(this.TerrainHeightOptionValueText);
            this.TerrainBrushHeightOptionGroupBox.Controls.Add(this.TerrainHeightOptionHeightLockRadioButton);
            this.TerrainBrushHeightOptionGroupBox.Controls.Add(this.TerrainHeightOptionNoneRadioButton);
            this.TerrainBrushHeightOptionGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TerrainBrushHeightOptionGroupBox.Location = new System.Drawing.Point(0, 0);
            this.TerrainBrushHeightOptionGroupBox.Name = "TerrainBrushHeightOptionGroupBox";
            this.TerrainBrushHeightOptionGroupBox.Size = new System.Drawing.Size(256, 85);
            this.TerrainBrushHeightOptionGroupBox.TabIndex = 2;
            this.TerrainBrushHeightOptionGroupBox.TabStop = false;
            this.TerrainBrushHeightOptionGroupBox.Text = "HeightOption";
            this.TerrainBrushHeightOptionGroupBox.Visible = false;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(34, 43);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(37, 12);
            this.label12.TabIndex = 31;
            this.label12.Text = "Value";
            // 
            // TerrainHeightOptionValueText
            // 
            this.TerrainHeightOptionValueText.AllowDrop = true;
            this.TerrainHeightOptionValueText.Location = new System.Drawing.Point(19, 60);
            this.TerrainHeightOptionValueText.Margin = new System.Windows.Forms.Padding(1);
            this.TerrainHeightOptionValueText.Name = "TerrainHeightOptionValueText";
            this.TerrainHeightOptionValueText.Size = new System.Drawing.Size(61, 21);
            this.TerrainHeightOptionValueText.TabIndex = 29;
            // 
            // TerrainHeightOptionHeightLockRadioButton
            // 
            this.TerrainHeightOptionHeightLockRadioButton.AutoSize = true;
            this.TerrainHeightOptionHeightLockRadioButton.Location = new System.Drawing.Point(78, 20);
            this.TerrainHeightOptionHeightLockRadioButton.Name = "TerrainHeightOptionHeightLockRadioButton";
            this.TerrainHeightOptionHeightLockRadioButton.Size = new System.Drawing.Size(85, 16);
            this.TerrainHeightOptionHeightLockRadioButton.TabIndex = 1;
            this.TerrainHeightOptionHeightLockRadioButton.Text = "HeightLock";
            this.TerrainHeightOptionHeightLockRadioButton.UseVisualStyleBackColor = true;
            // 
            // TerrainHeightOptionNoneRadioButton
            // 
            this.TerrainHeightOptionNoneRadioButton.AutoSize = true;
            this.TerrainHeightOptionNoneRadioButton.Checked = true;
            this.TerrainHeightOptionNoneRadioButton.Location = new System.Drawing.Point(19, 20);
            this.TerrainHeightOptionNoneRadioButton.Name = "TerrainHeightOptionNoneRadioButton";
            this.TerrainHeightOptionNoneRadioButton.Size = new System.Drawing.Size(53, 16);
            this.TerrainHeightOptionNoneRadioButton.TabIndex = 0;
            this.TerrainHeightOptionNoneRadioButton.TabStop = true;
            this.TerrainHeightOptionNoneRadioButton.Text = "None";
            this.TerrainHeightOptionNoneRadioButton.UseVisualStyleBackColor = true;
            // 
            // testPanel1
            // 
            this.testPanel1.Controls.Add(this.TerrainBrushSplattingGroupBox);
            this.testPanel1.Controls.Add(this.TerrainBrushHeightGroupBox);
            this.testPanel1.Location = new System.Drawing.Point(100, 151);
            this.testPanel1.Name = "testPanel1";
            this.testPanel1.Size = new System.Drawing.Size(160, 71);
            this.testPanel1.TabIndex = 27;
            // 
            // TerrainBrushSplattingGroupBox
            // 
            this.TerrainBrushSplattingGroupBox.Controls.Add(this.TerrainSplattingStage4RadioButton);
            this.TerrainBrushSplattingGroupBox.Controls.Add(this.TerrainSplattingStage2RadioButton);
            this.TerrainBrushSplattingGroupBox.Controls.Add(this.TerrainSplattingStage3RadioButton);
            this.TerrainBrushSplattingGroupBox.Controls.Add(this.TerrainSplattingStage1RadioButton);
            this.TerrainBrushSplattingGroupBox.Location = new System.Drawing.Point(0, 0);
            this.TerrainBrushSplattingGroupBox.Name = "TerrainBrushSplattingGroupBox";
            this.TerrainBrushSplattingGroupBox.Size = new System.Drawing.Size(160, 71);
            this.TerrainBrushSplattingGroupBox.TabIndex = 26;
            this.TerrainBrushSplattingGroupBox.TabStop = false;
            this.TerrainBrushSplattingGroupBox.Text = "SplattingImageFile";
            this.TerrainBrushSplattingGroupBox.Visible = false;
            // 
            // TerrainSplattingStage4RadioButton
            // 
            this.TerrainSplattingStage4RadioButton.AutoSize = true;
            this.TerrainSplattingStage4RadioButton.Location = new System.Drawing.Point(74, 42);
            this.TerrainSplattingStage4RadioButton.Name = "TerrainSplattingStage4RadioButton";
            this.TerrainSplattingStage4RadioButton.Size = new System.Drawing.Size(61, 16);
            this.TerrainSplattingStage4RadioButton.TabIndex = 3;
            this.TerrainSplattingStage4RadioButton.TabStop = true;
            this.TerrainSplattingStage4RadioButton.Text = "Stage4";
            this.TerrainSplattingStage4RadioButton.UseVisualStyleBackColor = true;
            // 
            // TerrainSplattingStage2RadioButton
            // 
            this.TerrainSplattingStage2RadioButton.AutoSize = true;
            this.TerrainSplattingStage2RadioButton.Location = new System.Drawing.Point(74, 19);
            this.TerrainSplattingStage2RadioButton.Name = "TerrainSplattingStage2RadioButton";
            this.TerrainSplattingStage2RadioButton.Size = new System.Drawing.Size(61, 16);
            this.TerrainSplattingStage2RadioButton.TabIndex = 2;
            this.TerrainSplattingStage2RadioButton.TabStop = true;
            this.TerrainSplattingStage2RadioButton.Text = "Stage2";
            this.TerrainSplattingStage2RadioButton.UseVisualStyleBackColor = true;
            // 
            // TerrainSplattingStage3RadioButton
            // 
            this.TerrainSplattingStage3RadioButton.AutoSize = true;
            this.TerrainSplattingStage3RadioButton.Location = new System.Drawing.Point(7, 42);
            this.TerrainSplattingStage3RadioButton.Name = "TerrainSplattingStage3RadioButton";
            this.TerrainSplattingStage3RadioButton.Size = new System.Drawing.Size(61, 16);
            this.TerrainSplattingStage3RadioButton.TabIndex = 1;
            this.TerrainSplattingStage3RadioButton.TabStop = true;
            this.TerrainSplattingStage3RadioButton.Text = "Stage3";
            this.TerrainSplattingStage3RadioButton.UseVisualStyleBackColor = true;
            // 
            // TerrainSplattingStage1RadioButton
            // 
            this.TerrainSplattingStage1RadioButton.AutoSize = true;
            this.TerrainSplattingStage1RadioButton.Location = new System.Drawing.Point(7, 19);
            this.TerrainSplattingStage1RadioButton.Name = "TerrainSplattingStage1RadioButton";
            this.TerrainSplattingStage1RadioButton.Size = new System.Drawing.Size(61, 16);
            this.TerrainSplattingStage1RadioButton.TabIndex = 0;
            this.TerrainSplattingStage1RadioButton.TabStop = true;
            this.TerrainSplattingStage1RadioButton.Text = "Stage1";
            this.TerrainSplattingStage1RadioButton.UseVisualStyleBackColor = true;
            // 
            // TerrainBrushHeightGroupBox
            // 
            this.TerrainBrushHeightGroupBox.Controls.Add(this.TerrainBushTypeCircleRadioButton);
            this.TerrainBrushHeightGroupBox.Controls.Add(this.TerrainBushTypeRectRadioButton);
            this.TerrainBrushHeightGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TerrainBrushHeightGroupBox.Location = new System.Drawing.Point(0, 0);
            this.TerrainBrushHeightGroupBox.Name = "TerrainBrushHeightGroupBox";
            this.TerrainBrushHeightGroupBox.Size = new System.Drawing.Size(160, 71);
            this.TerrainBrushHeightGroupBox.TabIndex = 27;
            this.TerrainBrushHeightGroupBox.TabStop = false;
            this.TerrainBrushHeightGroupBox.Text = "BrushShape";
            // 
            // TerrainBushTypeCircleRadioButton
            // 
            this.TerrainBushTypeCircleRadioButton.AutoSize = true;
            this.TerrainBushTypeCircleRadioButton.Location = new System.Drawing.Point(7, 42);
            this.TerrainBushTypeCircleRadioButton.Name = "TerrainBushTypeCircleRadioButton";
            this.TerrainBushTypeCircleRadioButton.Size = new System.Drawing.Size(89, 16);
            this.TerrainBushTypeCircleRadioButton.TabIndex = 1;
            this.TerrainBushTypeCircleRadioButton.TabStop = true;
            this.TerrainBushTypeCircleRadioButton.Text = "CircleBrush";
            this.TerrainBushTypeCircleRadioButton.UseVisualStyleBackColor = true;
            // 
            // TerrainBushTypeRectRadioButton
            // 
            this.TerrainBushTypeRectRadioButton.AutoSize = true;
            this.TerrainBushTypeRectRadioButton.Location = new System.Drawing.Point(7, 19);
            this.TerrainBushTypeRectRadioButton.Name = "TerrainBushTypeRectRadioButton";
            this.TerrainBushTypeRectRadioButton.Size = new System.Drawing.Size(112, 16);
            this.TerrainBushTypeRectRadioButton.TabIndex = 0;
            this.TerrainBushTypeRectRadioButton.TabStop = true;
            this.TerrainBushTypeRectRadioButton.Text = "RectangleBrush";
            this.TerrainBushTypeRectRadioButton.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.TerrainSplattingRadioButton);
            this.groupBox1.Controls.Add(this.TerrainHeightRadioButton);
            this.groupBox1.Location = new System.Drawing.Point(8, 151);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(88, 71);
            this.groupBox1.TabIndex = 25;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Brush";
            // 
            // TerrainSplattingRadioButton
            // 
            this.TerrainSplattingRadioButton.AutoSize = true;
            this.TerrainSplattingRadioButton.Location = new System.Drawing.Point(11, 42);
            this.TerrainSplattingRadioButton.Name = "TerrainSplattingRadioButton";
            this.TerrainSplattingRadioButton.Size = new System.Drawing.Size(71, 16);
            this.TerrainSplattingRadioButton.TabIndex = 24;
            this.TerrainSplattingRadioButton.TabStop = true;
            this.TerrainSplattingRadioButton.Text = "Splatting";
            this.TerrainSplattingRadioButton.UseVisualStyleBackColor = true;
            this.TerrainSplattingRadioButton.CheckedChanged += new System.EventHandler(this.TerrainSplattingRadioButton_CheckedChanged);
            // 
            // TerrainHeightRadioButton
            // 
            this.TerrainHeightRadioButton.AutoSize = true;
            this.TerrainHeightRadioButton.Location = new System.Drawing.Point(11, 20);
            this.TerrainHeightRadioButton.Name = "TerrainHeightRadioButton";
            this.TerrainHeightRadioButton.Size = new System.Drawing.Size(58, 16);
            this.TerrainHeightRadioButton.TabIndex = 23;
            this.TerrainHeightRadioButton.TabStop = true;
            this.TerrainHeightRadioButton.Text = "Height";
            this.TerrainHeightRadioButton.UseVisualStyleBackColor = true;
            // 
            // TerrainStage4FileText
            // 
            this.TerrainStage4FileText.AllowDrop = true;
            this.TerrainStage4FileText.Location = new System.Drawing.Point(70, 126);
            this.TerrainStage4FileText.Margin = new System.Windows.Forms.Padding(1);
            this.TerrainStage4FileText.Name = "TerrainStage4FileText";
            this.TerrainStage4FileText.Size = new System.Drawing.Size(61, 21);
            this.TerrainStage4FileText.TabIndex = 22;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(4, 131);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(63, 12);
            this.label13.TabIndex = 21;
            this.label13.Text = "Stage4File";
            // 
            // TerrainStage3FileText
            // 
            this.TerrainStage3FileText.AllowDrop = true;
            this.TerrainStage3FileText.Location = new System.Drawing.Point(201, 103);
            this.TerrainStage3FileText.Margin = new System.Windows.Forms.Padding(1);
            this.TerrainStage3FileText.Name = "TerrainStage3FileText";
            this.TerrainStage3FileText.Size = new System.Drawing.Size(61, 21);
            this.TerrainStage3FileText.TabIndex = 20;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(135, 108);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(63, 12);
            this.label10.TabIndex = 19;
            this.label10.Text = "Stage3File";
            // 
            // TerrainStage2FileText
            // 
            this.TerrainStage2FileText.AllowDrop = true;
            this.TerrainStage2FileText.Location = new System.Drawing.Point(70, 103);
            this.TerrainStage2FileText.Margin = new System.Windows.Forms.Padding(1);
            this.TerrainStage2FileText.Name = "TerrainStage2FileText";
            this.TerrainStage2FileText.Size = new System.Drawing.Size(61, 21);
            this.TerrainStage2FileText.TabIndex = 18;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(4, 108);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(63, 12);
            this.label11.TabIndex = 17;
            this.label11.Text = "Stage2File";
            // 
            // TerrainStage1FileText
            // 
            this.TerrainStage1FileText.AllowDrop = true;
            this.TerrainStage1FileText.Location = new System.Drawing.Point(201, 80);
            this.TerrainStage1FileText.Margin = new System.Windows.Forms.Padding(1);
            this.TerrainStage1FileText.Name = "TerrainStage1FileText";
            this.TerrainStage1FileText.Size = new System.Drawing.Size(61, 21);
            this.TerrainStage1FileText.TabIndex = 16;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(135, 85);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(63, 12);
            this.label9.TabIndex = 15;
            this.label9.Text = "Stage1File";
            // 
            // TerrainDiffuseFileText
            // 
            this.TerrainDiffuseFileText.AllowDrop = true;
            this.TerrainDiffuseFileText.Location = new System.Drawing.Point(70, 80);
            this.TerrainDiffuseFileText.Margin = new System.Windows.Forms.Padding(1);
            this.TerrainDiffuseFileText.Name = "TerrainDiffuseFileText";
            this.TerrainDiffuseFileText.Size = new System.Drawing.Size(61, 21);
            this.TerrainDiffuseFileText.TabIndex = 14;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(4, 85);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(63, 12);
            this.label8.TabIndex = 13;
            this.label8.Text = "DiffuseFile";
            // 
            // TerrainAmbientColorChangeButton
            // 
            this.TerrainAmbientColorChangeButton.Location = new System.Drawing.Point(222, 53);
            this.TerrainAmbientColorChangeButton.Name = "TerrainAmbientColorChangeButton";
            this.TerrainAmbientColorChangeButton.Size = new System.Drawing.Size(22, 23);
            this.TerrainAmbientColorChangeButton.TabIndex = 12;
            this.TerrainAmbientColorChangeButton.UseVisualStyleBackColor = true;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(140, 58);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(81, 12);
            this.label7.TabIndex = 11;
            this.label7.Text = "AmbientColor";
            // 
            // TerrainDiffuseColorChangeButton
            // 
            this.TerrainDiffuseColorChangeButton.Location = new System.Drawing.Point(104, 53);
            this.TerrainDiffuseColorChangeButton.Name = "TerrainDiffuseColorChangeButton";
            this.TerrainDiffuseColorChangeButton.Size = new System.Drawing.Size(22, 23);
            this.TerrainDiffuseColorChangeButton.TabIndex = 10;
            this.TerrainDiffuseColorChangeButton.UseVisualStyleBackColor = true;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(29, 58);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(73, 12);
            this.label6.TabIndex = 9;
            this.label6.Text = "DiffuseColor";
            // 
            // TerrainSizeChangeButton
            // 
            this.TerrainSizeChangeButton.Location = new System.Drawing.Point(230, 27);
            this.TerrainSizeChangeButton.Name = "TerrainSizeChangeButton";
            this.TerrainSizeChangeButton.Size = new System.Drawing.Size(30, 23);
            this.TerrainSizeChangeButton.TabIndex = 8;
            this.TerrainSizeChangeButton.Text = "뿅";
            this.TerrainSizeChangeButton.UseVisualStyleBackColor = true;
            // 
            // TerrainHeightText
            // 
            this.TerrainHeightText.AllowDrop = true;
            this.TerrainHeightText.Location = new System.Drawing.Point(161, 28);
            this.TerrainHeightText.Margin = new System.Windows.Forms.Padding(1);
            this.TerrainHeightText.Name = "TerrainHeightText";
            this.TerrainHeightText.Size = new System.Drawing.Size(61, 21);
            this.TerrainHeightText.TabIndex = 7;
            // 
            // TerrainWidthText
            // 
            this.TerrainWidthText.AllowDrop = true;
            this.TerrainWidthText.Location = new System.Drawing.Point(47, 28);
            this.TerrainWidthText.Margin = new System.Windows.Forms.Padding(1);
            this.TerrainWidthText.Name = "TerrainWidthText";
            this.TerrainWidthText.Size = new System.Drawing.Size(61, 21);
            this.TerrainWidthText.TabIndex = 6;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(116, 33);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(40, 12);
            this.label5.TabIndex = 5;
            this.label5.Text = "Height";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 33);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 12);
            this.label4.TabIndex = 4;
            this.label4.Text = "WIdth";
            // 
            // TerrainShaderFilePathText
            // 
            this.TerrainShaderFilePathText.AllowDrop = true;
            this.TerrainShaderFilePathText.Location = new System.Drawing.Point(98, 4);
            this.TerrainShaderFilePathText.Margin = new System.Windows.Forms.Padding(1);
            this.TerrainShaderFilePathText.Name = "TerrainShaderFilePathText";
            this.TerrainShaderFilePathText.Size = new System.Drawing.Size(170, 21);
            this.TerrainShaderFilePathText.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 9);
            this.label2.Margin = new System.Windows.Forms.Padding(1, 0, 1, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(90, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "ShaderFilePath";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ModelTab
            // 
            this.ModelTab.Controls.Add(this.ModelTextureFileText);
            this.ModelTab.Controls.Add(this.ModelDiffuseFileText);
            this.ModelTab.Controls.Add(this.ModelShaderFileText);
            this.ModelTab.Controls.Add(this.label20);
            this.ModelTab.Controls.Add(this.label19);
            this.ModelTab.Controls.Add(this.label18);
            this.ModelTab.Controls.Add(this.ModelSZText);
            this.ModelTab.Controls.Add(this.ModelSYText);
            this.ModelTab.Controls.Add(this.ModelSXText);
            this.ModelTab.Controls.Add(this.ModelRZText);
            this.ModelTab.Controls.Add(this.ModelRYText);
            this.ModelTab.Controls.Add(this.ModelRXText);
            this.ModelTab.Controls.Add(this.ModelTZText);
            this.ModelTab.Controls.Add(this.ModelTYText);
            this.ModelTab.Controls.Add(this.ModelTXText);
            this.ModelTab.Controls.Add(this.label17);
            this.ModelTab.Controls.Add(this.label16);
            this.ModelTab.Controls.Add(this.label15);
            this.ModelTab.Controls.Add(this.ModelModelNameText);
            this.ModelTab.Controls.Add(this.label3);
            this.ModelTab.Location = new System.Drawing.Point(4, 22);
            this.ModelTab.Name = "ModelTab";
            this.ModelTab.Size = new System.Drawing.Size(268, 313);
            this.ModelTab.TabIndex = 2;
            this.ModelTab.Text = "Model";
            this.ModelTab.UseVisualStyleBackColor = true;
            // 
            // ModelTextureFileText
            // 
            this.ModelTextureFileText.Location = new System.Drawing.Point(86, 195);
            this.ModelTextureFileText.Name = "ModelTextureFileText";
            this.ModelTextureFileText.Size = new System.Drawing.Size(175, 21);
            this.ModelTextureFileText.TabIndex = 19;
            // 
            // ModelDiffuseFileText
            // 
            this.ModelDiffuseFileText.Location = new System.Drawing.Point(86, 164);
            this.ModelDiffuseFileText.Name = "ModelDiffuseFileText";
            this.ModelDiffuseFileText.Size = new System.Drawing.Size(175, 21);
            this.ModelDiffuseFileText.TabIndex = 18;
            // 
            // ModelShaderFileText
            // 
            this.ModelShaderFileText.Location = new System.Drawing.Point(86, 135);
            this.ModelShaderFileText.Name = "ModelShaderFileText";
            this.ModelShaderFileText.Size = new System.Drawing.Size(175, 21);
            this.ModelShaderFileText.TabIndex = 17;
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(12, 200);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(68, 12);
            this.label20.TabIndex = 16;
            this.label20.Text = "TextureFile";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(7, 169);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(73, 12);
            this.label19.TabIndex = 15;
            this.label19.Text = "DiffuseColor";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(15, 140);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(65, 12);
            this.label18.TabIndex = 14;
            this.label18.Text = "ShaderFile";
            // 
            // ModelSZText
            // 
            this.ModelSZText.Location = new System.Drawing.Point(206, 98);
            this.ModelSZText.Name = "ModelSZText";
            this.ModelSZText.Size = new System.Drawing.Size(54, 21);
            this.ModelSZText.TabIndex = 13;
            // 
            // ModelSYText
            // 
            this.ModelSYText.Location = new System.Drawing.Point(146, 98);
            this.ModelSYText.Name = "ModelSYText";
            this.ModelSYText.Size = new System.Drawing.Size(54, 21);
            this.ModelSYText.TabIndex = 12;
            // 
            // ModelSXText
            // 
            this.ModelSXText.Location = new System.Drawing.Point(86, 98);
            this.ModelSXText.Name = "ModelSXText";
            this.ModelSXText.Size = new System.Drawing.Size(54, 21);
            this.ModelSXText.TabIndex = 11;
            // 
            // ModelRZText
            // 
            this.ModelRZText.Location = new System.Drawing.Point(206, 68);
            this.ModelRZText.Name = "ModelRZText";
            this.ModelRZText.Size = new System.Drawing.Size(54, 21);
            this.ModelRZText.TabIndex = 10;
            // 
            // ModelRYText
            // 
            this.ModelRYText.Location = new System.Drawing.Point(146, 68);
            this.ModelRYText.Name = "ModelRYText";
            this.ModelRYText.Size = new System.Drawing.Size(54, 21);
            this.ModelRYText.TabIndex = 9;
            // 
            // ModelRXText
            // 
            this.ModelRXText.Location = new System.Drawing.Point(86, 68);
            this.ModelRXText.Name = "ModelRXText";
            this.ModelRXText.Size = new System.Drawing.Size(54, 21);
            this.ModelRXText.TabIndex = 8;
            // 
            // ModelTZText
            // 
            this.ModelTZText.Location = new System.Drawing.Point(206, 38);
            this.ModelTZText.Name = "ModelTZText";
            this.ModelTZText.Size = new System.Drawing.Size(54, 21);
            this.ModelTZText.TabIndex = 7;
            // 
            // ModelTYText
            // 
            this.ModelTYText.Location = new System.Drawing.Point(146, 38);
            this.ModelTYText.Name = "ModelTYText";
            this.ModelTYText.Size = new System.Drawing.Size(54, 21);
            this.ModelTYText.TabIndex = 6;
            // 
            // ModelTXText
            // 
            this.ModelTXText.Location = new System.Drawing.Point(86, 38);
            this.ModelTXText.Name = "ModelTXText";
            this.ModelTXText.Size = new System.Drawing.Size(54, 21);
            this.ModelTXText.TabIndex = 5;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(38, 101);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(13, 12);
            this.label17.TabIndex = 4;
            this.label17.Text = "S";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(38, 71);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(13, 12);
            this.label16.TabIndex = 3;
            this.label16.Text = "R";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(38, 41);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(13, 12);
            this.label15.TabIndex = 2;
            this.label15.Text = "T";
            // 
            // ModelModelNameText
            // 
            this.ModelModelNameText.Location = new System.Drawing.Point(86, 7);
            this.ModelModelNameText.Name = "ModelModelNameText";
            this.ModelModelNameText.Size = new System.Drawing.Size(175, 21);
            this.ModelModelNameText.TabIndex = 1;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 13);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(74, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "ModelName";
            // 
            // RightSplitter
            // 
            this.RightSplitter.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.RightSplitter.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.RightSplitter.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.RightSplitter.Location = new System.Drawing.Point(0, 339);
            this.RightSplitter.Margin = new System.Windows.Forms.Padding(1);
            this.RightSplitter.MinSize = 35;
            this.RightSplitter.Name = "RightSplitter";
            this.RightSplitter.Size = new System.Drawing.Size(276, 10);
            this.RightSplitter.TabIndex = 0;
            this.RightSplitter.TabStop = false;
            // 
            // ProjectTab
            // 
            this.ProjectTab.Controls.Add(this.ShaderTab);
            this.ProjectTab.Controls.Add(this.TerrainTap);
            this.ProjectTab.Controls.Add(this.ModelFileTab);
            this.ProjectTab.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ProjectTab.Location = new System.Drawing.Point(0, 0);
            this.ProjectTab.Margin = new System.Windows.Forms.Padding(1);
            this.ProjectTab.Name = "ProjectTab";
            this.ProjectTab.SelectedIndex = 0;
            this.ProjectTab.Size = new System.Drawing.Size(276, 272);
            this.ProjectTab.TabIndex = 0;
            // 
            // ShaderTab
            // 
            this.ShaderTab.Controls.Add(this.RefreshShaderFileList);
            this.ShaderTab.Controls.Add(this.ShaderFileList);
            this.ShaderTab.Location = new System.Drawing.Point(4, 22);
            this.ShaderTab.Margin = new System.Windows.Forms.Padding(1);
            this.ShaderTab.Name = "ShaderTab";
            this.ShaderTab.Padding = new System.Windows.Forms.Padding(1);
            this.ShaderTab.Size = new System.Drawing.Size(268, 246);
            this.ShaderTab.TabIndex = 0;
            this.ShaderTab.Text = "Shader";
            this.ShaderTab.UseVisualStyleBackColor = true;
            // 
            // RefreshShaderFileList
            // 
            this.RefreshShaderFileList.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.RefreshShaderFileList.Location = new System.Drawing.Point(8, 216);
            this.RefreshShaderFileList.Margin = new System.Windows.Forms.Padding(1);
            this.RefreshShaderFileList.Name = "RefreshShaderFileList";
            this.RefreshShaderFileList.Size = new System.Drawing.Size(250, 24);
            this.RefreshShaderFileList.TabIndex = 2;
            this.RefreshShaderFileList.Text = "새로고침";
            this.RefreshShaderFileList.UseVisualStyleBackColor = true;
            // 
            // ShaderFileList
            // 
            this.ShaderFileList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ShaderFileList.FormattingEnabled = true;
            this.ShaderFileList.ItemHeight = 12;
            this.ShaderFileList.Location = new System.Drawing.Point(8, 10);
            this.ShaderFileList.Margin = new System.Windows.Forms.Padding(1);
            this.ShaderFileList.Name = "ShaderFileList";
            this.ShaderFileList.Size = new System.Drawing.Size(253, 184);
            this.ShaderFileList.TabIndex = 1;
            // 
            // TerrainTap
            // 
            this.TerrainTap.Controls.Add(this.RefreshTextureFileList);
            this.TerrainTap.Controls.Add(this.TextureFileList);
            this.TerrainTap.Location = new System.Drawing.Point(4, 22);
            this.TerrainTap.Name = "TerrainTap";
            this.TerrainTap.Size = new System.Drawing.Size(268, 246);
            this.TerrainTap.TabIndex = 1;
            this.TerrainTap.Text = "Texture";
            this.TerrainTap.UseVisualStyleBackColor = true;
            // 
            // RefreshTextureFileList
            // 
            this.RefreshTextureFileList.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.RefreshTextureFileList.Location = new System.Drawing.Point(8, 216);
            this.RefreshTextureFileList.Margin = new System.Windows.Forms.Padding(1);
            this.RefreshTextureFileList.Name = "RefreshTextureFileList";
            this.RefreshTextureFileList.Size = new System.Drawing.Size(250, 24);
            this.RefreshTextureFileList.TabIndex = 3;
            this.RefreshTextureFileList.Text = "새로고침";
            this.RefreshTextureFileList.UseVisualStyleBackColor = true;
            // 
            // TextureFileList
            // 
            this.TextureFileList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TextureFileList.FormattingEnabled = true;
            this.TextureFileList.ItemHeight = 12;
            this.TextureFileList.Location = new System.Drawing.Point(8, 10);
            this.TextureFileList.Margin = new System.Windows.Forms.Padding(1);
            this.TextureFileList.Name = "TextureFileList";
            this.TextureFileList.Size = new System.Drawing.Size(253, 184);
            this.TextureFileList.TabIndex = 2;
            // 
            // ModelFileTab
            // 
            this.ModelFileTab.Controls.Add(this.RefreshModelFileList);
            this.ModelFileTab.Controls.Add(this.ModelFileList);
            this.ModelFileTab.Location = new System.Drawing.Point(4, 22);
            this.ModelFileTab.Name = "ModelFileTab";
            this.ModelFileTab.Size = new System.Drawing.Size(268, 246);
            this.ModelFileTab.TabIndex = 2;
            this.ModelFileTab.Text = "Model";
            this.ModelFileTab.UseVisualStyleBackColor = true;
            // 
            // RefreshModelFileList
            // 
            this.RefreshModelFileList.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.RefreshModelFileList.Location = new System.Drawing.Point(8, 216);
            this.RefreshModelFileList.Margin = new System.Windows.Forms.Padding(1);
            this.RefreshModelFileList.Name = "RefreshModelFileList";
            this.RefreshModelFileList.Size = new System.Drawing.Size(250, 24);
            this.RefreshModelFileList.TabIndex = 5;
            this.RefreshModelFileList.Text = "새로고침";
            this.RefreshModelFileList.UseVisualStyleBackColor = true;
            // 
            // ModelFileList
            // 
            this.ModelFileList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ModelFileList.FormattingEnabled = true;
            this.ModelFileList.ItemHeight = 12;
            this.ModelFileList.Location = new System.Drawing.Point(8, 10);
            this.ModelFileList.Margin = new System.Windows.Forms.Padding(1);
            this.ModelFileList.Name = "ModelFileList";
            this.ModelFileList.Size = new System.Drawing.Size(253, 184);
            this.ModelFileList.TabIndex = 4;
            // 
            // BottomPanel
            // 
            this.BottomPanel.Controls.Add(this.LogListView);
            this.BottomPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.BottomPanel.Location = new System.Drawing.Point(0, 476);
            this.BottomPanel.Margin = new System.Windows.Forms.Padding(1);
            this.BottomPanel.Name = "BottomPanel";
            this.BottomPanel.Size = new System.Drawing.Size(801, 147);
            this.BottomPanel.TabIndex = 3;
            // 
            // LogListView
            // 
            this.LogListView.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.LogListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2});
            this.LogListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.LogListView.GridLines = true;
            this.LogListView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this.LogListView.Location = new System.Drawing.Point(0, 0);
            this.LogListView.Margin = new System.Windows.Forms.Padding(1);
            this.LogListView.Name = "LogListView";
            this.LogListView.Size = new System.Drawing.Size(801, 147);
            this.LogListView.TabIndex = 0;
            this.LogListView.UseCompatibleStateImageBehavior = false;
            this.LogListView.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Width = 1000;
            // 
            // MainPanel
            // 
            this.MainPanel.Controls.Add(this.RenderBox);
            this.MainPanel.Controls.Add(this.menuStrip1);
            this.MainPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.MainPanel.Location = new System.Drawing.Point(0, 0);
            this.MainPanel.Margin = new System.Windows.Forms.Padding(1);
            this.MainPanel.Name = "MainPanel";
            this.MainPanel.Size = new System.Drawing.Size(801, 476);
            this.MainPanel.TabIndex = 5;
            // 
            // RenderBox
            // 
            this.RenderBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.RenderBox.Location = new System.Drawing.Point(0, 24);
            this.RenderBox.Margin = new System.Windows.Forms.Padding(1);
            this.RenderBox.Name = "RenderBox";
            this.RenderBox.Size = new System.Drawing.Size(801, 452);
            this.RenderBox.TabIndex = 0;
            this.RenderBox.TabStop = false;
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(40, 40);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.FileMenu,
            this.fbx변환ConverterToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(2, 1, 0, 1);
            this.menuStrip1.Size = new System.Drawing.Size(801, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // FileMenu
            // 
            this.FileMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.FileOpenMenu,
            this.FileSaveMenu,
            this.toolStripMenuItem1,
            this.FileExitMenu});
            this.FileMenu.Name = "FileMenu";
            this.FileMenu.Size = new System.Drawing.Size(69, 22);
            this.FileMenu.Text = "파일(&File)";
            // 
            // FileOpenMenu
            // 
            this.FileOpenMenu.Name = "FileOpenMenu";
            this.FileOpenMenu.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.FileOpenMenu.Size = new System.Drawing.Size(202, 22);
            this.FileOpenMenu.Text = "불러오기(&Open)";
            // 
            // FileSaveMenu
            // 
            this.FileSaveMenu.Name = "FileSaveMenu";
            this.FileSaveMenu.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.FileSaveMenu.Size = new System.Drawing.Size(202, 22);
            this.FileSaveMenu.Text = "저장하기(&Save)";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(199, 6);
            // 
            // FileExitMenu
            // 
            this.FileExitMenu.Name = "FileExitMenu";
            this.FileExitMenu.Size = new System.Drawing.Size(202, 22);
            this.FileExitMenu.Text = "종료(E&xit)";
            // 
            // fbx변환ConverterToolStripMenuItem
            // 
            this.fbx변환ConverterToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ConvertFbxFile});
            this.fbx변환ConverterToolStripMenuItem.Name = "fbx변환ConverterToolStripMenuItem";
            this.fbx변환ConverterToolStripMenuItem.Size = new System.Drawing.Size(122, 22);
            this.fbx변환ConverterToolStripMenuItem.Text = "Fbx변환(&Converter)";
            // 
            // ConvertFbxFile
            // 
            this.ConvertFbxFile.Name = "ConvertFbxFile";
            this.ConvertFbxFile.Size = new System.Drawing.Size(171, 22);
            this.ConvertFbxFile.Text = "모델변환(&Change)";
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1077, 623);
            this.Controls.Add(this.MainPanel);
            this.Controls.Add(this.BottomPanel);
            this.Controls.Add(this.RightPanel);
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(1);
            this.Name = "MainForm";
            this.Text = "Map Editor";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.RightPanel.ResumeLayout(false);
            this.RightSplitContainer.Panel1.ResumeLayout(false);
            this.RightSplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.RightSplitContainer)).EndInit();
            this.RightSplitContainer.ResumeLayout(false);
            this.InpectorTab.ResumeLayout(false);
            this.SkyTab.ResumeLayout(false);
            this.SkyTab.PerformLayout();
            this.TerrainTab.ResumeLayout(false);
            this.TerrainTab.PerformLayout();
            this.TerrainBrushOptionPanel.ResumeLayout(false);
            this.TerrainBrushHeightOptionGroupBox.ResumeLayout(false);
            this.TerrainBrushHeightOptionGroupBox.PerformLayout();
            this.testPanel1.ResumeLayout(false);
            this.TerrainBrushSplattingGroupBox.ResumeLayout(false);
            this.TerrainBrushSplattingGroupBox.PerformLayout();
            this.TerrainBrushHeightGroupBox.ResumeLayout(false);
            this.TerrainBrushHeightGroupBox.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ModelTab.ResumeLayout(false);
            this.ModelTab.PerformLayout();
            this.ProjectTab.ResumeLayout(false);
            this.ShaderTab.ResumeLayout(false);
            this.TerrainTap.ResumeLayout(false);
            this.ModelFileTab.ResumeLayout(false);
            this.BottomPanel.ResumeLayout(false);
            this.MainPanel.ResumeLayout(false);
            this.MainPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.RenderBox)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel RightPanel;
        private System.Windows.Forms.Panel BottomPanel;
        private System.Windows.Forms.ListView LogListView;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.Panel MainPanel;
        private System.Windows.Forms.PictureBox RenderBox;
        private System.Windows.Forms.SplitContainer RightSplitContainer;
        private System.Windows.Forms.TabControl InpectorTab;
        private System.Windows.Forms.TabPage SkyTab;
        private System.Windows.Forms.Splitter RightSplitter;
        private System.Windows.Forms.TabControl ProjectTab;
        private System.Windows.Forms.TabPage ShaderTab;
        private System.Windows.Forms.ListBox ShaderFileList;
        private System.Windows.Forms.Button RefreshShaderFileList;
        private System.Windows.Forms.TextBox SkyShaderFilePathText;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem FileMenu;
        private System.Windows.Forms.ToolStripMenuItem FileOpenMenu;
        private System.Windows.Forms.ToolStripMenuItem FileSaveMenu;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem FileExitMenu;
        private System.Windows.Forms.TabPage TerrainTap;
        private System.Windows.Forms.Button RefreshTextureFileList;
        private System.Windows.Forms.ListBox TextureFileList;
        private System.Windows.Forms.TabPage ModelFileTab;
        private System.Windows.Forms.Button RefreshModelFileList;
        private System.Windows.Forms.ListBox ModelFileList;
        private System.Windows.Forms.TabPage TerrainTab;
        private System.Windows.Forms.TextBox TerrainShaderFilePathText;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TabPage ModelTab;
        private System.Windows.Forms.TextBox TerrainHeightText;
        private System.Windows.Forms.TextBox TerrainWidthText;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button TerrainSizeChangeButton;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button TerrainDiffuseColorChangeButton;
        private System.Windows.Forms.ColorDialog colorDialog1;
        private System.Windows.Forms.Button TerrainAmbientColorChangeButton;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox TerrainStage4FileText;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox TerrainStage3FileText;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox TerrainStage2FileText;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox TerrainStage1FileText;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox TerrainDiffuseFileText;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton TerrainSplattingRadioButton;
        private System.Windows.Forms.RadioButton TerrainHeightRadioButton;
        private System.Windows.Forms.GroupBox TerrainBrushHeightGroupBox;
        private System.Windows.Forms.GroupBox TerrainBrushSplattingGroupBox;
        private System.Windows.Forms.RadioButton TerrainSplattingStage4RadioButton;
        private System.Windows.Forms.RadioButton TerrainSplattingStage2RadioButton;
        private System.Windows.Forms.RadioButton TerrainSplattingStage3RadioButton;
        private System.Windows.Forms.RadioButton TerrainSplattingStage1RadioButton;
        private System.Windows.Forms.RadioButton TerrainBushTypeCircleRadioButton;
        private System.Windows.Forms.RadioButton TerrainBushTypeRectRadioButton;
        private System.Windows.Forms.Panel testPanel1;
        private System.Windows.Forms.Panel TerrainBrushOptionPanel;
        private System.Windows.Forms.GroupBox TerrainBrushSpattingOptionGroupBox;
        private System.Windows.Forms.GroupBox TerrainBrushHeightOptionGroupBox;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox TerrainHeightOptionValueText;
        private System.Windows.Forms.RadioButton TerrainHeightOptionHeightLockRadioButton;
        private System.Windows.Forms.RadioButton TerrainHeightOptionNoneRadioButton;
        private System.Windows.Forms.TextBox TerrainBrushSizeText;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Button SkyApexColorButton;
        private System.Windows.Forms.Label llll;
        private System.Windows.Forms.Button SkyCenterColorButton;
        private System.Windows.Forms.Label lll;
        private System.Windows.Forms.ToolStripMenuItem fbx변환ConverterToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ConvertFbxFile;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox ModelModelNameText;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox ModelTextureFileText;
        private System.Windows.Forms.TextBox ModelDiffuseFileText;
        private System.Windows.Forms.TextBox ModelShaderFileText;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TextBox ModelSZText;
        private System.Windows.Forms.TextBox ModelSYText;
        private System.Windows.Forms.TextBox ModelSXText;
        private System.Windows.Forms.TextBox ModelRZText;
        private System.Windows.Forms.TextBox ModelRYText;
        private System.Windows.Forms.TextBox ModelRXText;
        private System.Windows.Forms.TextBox ModelTZText;
        private System.Windows.Forms.TextBox ModelTYText;
        private System.Windows.Forms.TextBox ModelTXText;
    }
}

