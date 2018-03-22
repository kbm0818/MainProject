using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Viewer
{
    class Helper
    {
        public static void SearchDirectory(ref List<string> list, string dir, string pattern)
        {
            foreach (string f in Directory.GetFiles(dir, pattern))
            {
                list.Add(f);
            }

            foreach (string d in Directory.GetDirectories(dir))
            {
                SearchDirectory(ref list, d, pattern);
            }//foreach(d)
        }
    }
}
