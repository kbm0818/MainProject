using System.Windows.Forms;

namespace Viewer
{
    class LogView
    {
        private static ListView _listView;
        public static ListView ListView
        {
            set { _listView = value; }
        }

        private static LogView _instance;
        public static LogView Instance
        {
            get
            {
                if (_instance == null)
                    _instance = new LogView();

                return _instance;
            }
        }

        private uint _lineCount = 0;
        public void Add(string text)
        {
            string number = _lineCount.ToString();
            if (number.Length < 2) number = "0" + number;

            ListViewItem item = new ListViewItem(number);
            item.SubItems.Add(text);
            _listView.Items.Add(item);

            _lineCount++;
        }
    }
}
