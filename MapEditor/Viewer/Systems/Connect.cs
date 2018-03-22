using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Viewer
{
    class Connect
    {
        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_Create(int handle, float width, float height);

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_Destroy();

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_Update();

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_Render();

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Cs_WndProc(PeekMsg message);

        [DllImport("Direct3D.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Cs_SetFocus(bool bFocus);   

        [StructLayout(LayoutKind.Sequential)]
        public struct PeekMsg
        {
            public IntPtr hWnd;
            public Message msg;
            public IntPtr wParam;
            public IntPtr lParam;
            public uint time;
            public System.Drawing.Point p;
        }

        [System.Security.SuppressUnmanagedCodeSecurity]
        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        public static extern bool PeekMessage
        (
            out PeekMsg msg
            , IntPtr hWnd
            , uint messageFilterMin
            , uint messageFilterMax
            , uint flags
        );

        private static PictureBox _renderBox;
        public static PictureBox RenderBox
        {
            set { _renderBox = value; }
        }

        public static void MouseEnter(object sender, EventArgs e)
        {
            Cs_SetFocus(true);
        }

        public static void MouseLeave(object sender, EventArgs e)
        {
            Cs_SetFocus(false);
        }

        public static void Create(object sender, EventArgs e)
        {
            float width = (float)_renderBox.Width;
            float height = (float)_renderBox.Height;
        
            Cs_Create(_renderBox.Handle.ToInt32(), width, height);
        }

        public static void Destroy(object sender, EventArgs e)
        {
            Cs_Destroy();
        }

        public static void Idle(object sender, EventArgs e)
        {
            PeekMsg msg;

            while (true)
            {
                bool isCheck = PeekMessage(out msg, IntPtr.Zero, 0, 0, 0);
                Cs_WndProc(msg);

                if (isCheck == true)
                    break;

                Cs_Update();
                Cs_Render();
            }//while(true)
        }

        public struct D3DXVECTOR3
        {
            public float x, y, z;
          
            public D3DXVECTOR3(float f1, float f2, float f3)
            {
                x = f1;
                y = f2;
                z = f3;
            }
        }
    }
}
