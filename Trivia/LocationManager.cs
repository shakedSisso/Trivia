using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Trivia
{
    public static class LocationManager
    {
        private static Point formLocation = new Point(100, 100);

        public static Point GetFormLocation()
        {
            return formLocation;
        }

        public static void SetFormLocation(Point location)
        {
            formLocation = location;
        }
    }
}
