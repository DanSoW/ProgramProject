using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace KursProject
{
    class FileString
    {
        public static bool CheckFullNameFile(string str, string ext)
        {
            if ((str.Length <= 0) || (ext.Length <= 0)
                || (str.Length < ext.Length)
                || (!CheckSymbol(str[0])) || (!CheckSymbol(str[str.Length - 1]))
                || (str.IndexOf('.') != str.LastIndexOf('.')))
                return false;
            
            string nameDirectory = "", nameFile = "";

            int point = str.IndexOf('.');
            for (int i = 0; i < point; i++)
                nameDirectory += str[i];
            point = str.LastIndexOf('\\');

            for (int i = (point + 1); (i < str.Length); i++)
                nameFile += str[i];
            if ((nameDirectory.Length <= 0) || (nameFile.Length <= 0)
                || (!FileString.CheckNameDirectory(nameDirectory))
                || (!FileString.CheckNameFile(nameFile, ".txt")))
                return false;

            return true;
        }
        public static bool CheckSymbol(char symbol)
        {
            // Проверка символа на корректность (цифра, символ из латинского алфавита, кириллица и альтернатива пробелу
            return (!((symbol == '\"') || (symbol == '\\')
                || (symbol == '*') || (symbol == '?') 
                || (symbol == '<') || (symbol == '>') 
                || (symbol == '/') || (symbol == '|')
                || (symbol == ':')));
        }
        public static bool CheckNameDirectory(string str)
        {
            //Проверка строки, содержащая название директории файла
            if ((str.Length <= 0) || (str.IndexOf('.') >= 0)
                || (str.IndexOf(':') != str.LastIndexOf(':')) || (str.IndexOf(':') < 0)
                || (!CheckSymbol(str[0])) 
                || ((!CheckSymbol(str[str.Length - 1])) && (str[str.Length - 1] != '\\')))
                return false;
            int point = str.IndexOf(':');

            if (str[point + 1] != '\\')
                return false;

            for (int i = 0; i < point; i++)
                if (!CheckSymbol(str[i]))
                    return false;
            
            for (int i = (point + 1); i < str.Length; i++)
                if ((str[i] != '\\') && (!CheckSymbol(str[i])) && (str[i] != ' '))
                    return false;
            
            int count = 0; //длина последовательности символов \\ в строке str
            for (int i = (point + 1); i < str.Length; i++)
            {
                if (str[i] == '\\')
                    count++;
                else if (count > 1)
                    return false;
                else
                    count = 0;
            }

            return true;
        }

        public static bool CheckNameFile(string str, string ext)
        {
            //Проверка имени файла
            if ((str.Length <= 0) || (str.IndexOf('.') != str.LastIndexOf('.'))
                || (!CheckSymbol(str[0])) || (!CheckSymbol(str[str.Length - 1]))
                || (ext[0] != '.'))
                return false;
            int point = str.IndexOf('.');
            if (point > 0)
            {

                if (!SubStrInStr(str, ext, point))
                    return false;

                for (int i = 0; i < point; i++)
                    if (!CheckSymbol(str[i]))
                        return false;

                return ((str.Length - point) == (ext.Length));
            }

            for (int i = 0; i < str.Length; i++)
                if (!CheckSymbol(str[i]))
                    return false;
            return true;
        }

        public static bool SubStrInStr(string base_string, string substr, int point)
        {
            //Данная функция проверяет, присутствует ли строка substr в строке base_string с индекса point включительно
            if ((base_string.Length <= substr.Length) ||
                (base_string.Length <= 0) || (substr.Length <= 0)
                || (point >= base_string.Length) || (point < 0))
                return false;

            int count = 0;
            for (int i = point, j = 0; (i < base_string.Length) && (j < substr.Length); i++, j++)
                if (base_string[i] == substr[j])
                    count++;

            return (count == substr.Length);
        }
    }
}
