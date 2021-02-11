using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Runtime.InteropServices;

/*Даны три квадратные матрицы A и B и С
. Если разность между сумой элементов ниже главной диагонали и суммой элементов выше главной диагонали матрицы A
 больше чем разность между сумой элементов ниже главной диагонали матрицы B
 минус сумма элементов ыше главной диагонали матрицы C то  (A+C)^T⋅2+B иначе 3⋅B+(A−C)^T
*/

namespace CSharp_Program
{
    public class Matrix
    {
        private int[][] data = null; //данные
        private int size; //размер матрицы
        public int Size
        {
            get
            {
                return size;
            }
        }

        private Matrix() { } //пустой конструктор запрещён к использованию

        public Matrix(int n) //конструктор принимающий размер
        {
            if (n <= 0)
                return;

            size = n;
            data = new int[size][];
            for (int i = 0; i < size; i++)
                data[i] = new int[size];
        }

        public Matrix(int[][] inputData) //конструктор принимающий данные
        {
            if ((inputData.Length == 0) || (inputData.Length != inputData[0].Length))
                return;

            size = inputData.Length;
            data = new int[size][];
            for(int i = 0; i < size; i++)
            {
                data[i] = new int[size];
                for (int j = 0; j < size; j++)
                    data[i][j] = inputData[i][j];
            }
        }

        private static Random rand = new Random();
        public void fillRandom(int min = -100, int max = 100) //Рандомное заполнение матрицы в определённом диапазоне
        {
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    data[i][j] = rand.Next(min, max);
        }

        public static bool matrixEquallyMatrix(Matrix A, Matrix B) //проверка двух матриц на равенство всех элементов
        {
            if (A.Size != B.size)
                return false;
            for (int i = 0; i < A.size; i++)
                for (int j = 0; j < A.size; j++)
                    if (A[i][j] != B[i][j])
                        return false;
            return true;
        }

        public int[] this[int index] //индексатор
        {
            get
            {
                if ((index >= 0) && (index <= size))
                    return data[index];
                return null;
            }
        }

        public static Matrix operator +(Matrix A, Matrix B) //перегруженный оператор +
        {
            if ((A == null) || (B == null)
                || (A.size != B.size))
                return null;

            Matrix C = new Matrix(A.size);
            for (int i = 0; i < C.size; i++)
                for (int j = 0; j < C.size; j++)
                    C[i][j] = A[i][j] + B[i][j];

            return C;
        }

        public static Matrix operator-(int c, Matrix A) //перегруженный оператор - с числом
        {
            return (((-1) * A) + c);
        }

        public static Matrix operator-(Matrix A, int c) //перегруженный оператор - с числом
        {
            var resultMatix = new Matrix(A.Size);
            for (var i = 0; i < A.Size; ++i)
            {
                for (var j = 0; j < A.Size; ++j)
                {
                    if (i == j)
                    {
                        resultMatix[i][j] = A[i][j] - c;
                    }
                    else
                    {
                        resultMatix[i][j] = A[i][j];
                    }
                }
            }
            return resultMatix;
        }

        public static Matrix operator+(int c, Matrix A) { //перегруженный оператор + с числом
            return (A + c);
        }
        public static Matrix operator +(Matrix A, int c) //перегруженный оператор + с числом
        {
            var resultMatix = new Matrix(A.Size);
            for (var i = 0; i < A.Size; ++i)
            {
                for (var j = 0; j < A.Size; ++j)
                {
                    if (i == j)
                    {
                        resultMatix[i][j] = A[i][j] + c;
                    }
                    else
                    {
                        resultMatix[i][j] = A[i][j];
                    }
                }
            }
            return resultMatix;
        }

        public static Matrix operator -(Matrix A, Matrix B) //перегруженный оператор - 
        {
            if ((A == null) || (B == null)
                || (A.size != B.size))
                return null;

            Matrix C = new Matrix(A.size);
            for (int i = 0; i < C.size; i++)
                for (int j = 0; j < C.size; j++)
                    C[i][j] = A[i][j] - B[i][j];

            return C;
        }

        public static Matrix operator *(Matrix A, int value) //перегруженный оператор * с числом
        {
            if (A == null)
                return null;

            Matrix B = new Matrix(A.size);
            for (int i = 0; i < B.size; i++)
                for (int j = 0; j < B.size; j++)
                    B[i][j] = (A[i][j] * value);

            return B;
        }

        public static Matrix operator*(int value, Matrix A) //перегруженный оператор * с числом
        {
            return (A * value);
        }

        public static Matrix operator *(Matrix A, Matrix B) //перегруженный оператор *
        {
            if ((A == null) || (B == null)
                || (A.size != B.size))
                return null;

            Matrix C = new Matrix(A.size);
            for (int i = 0; i < C.size; i++)
                for (int j = 0; j < C.size; j++)
                    for (int k = 0; k < C.size; k++)
                        C[i][j] += A[i][k] * B[k][j];
            return C;
        }

        public static Matrix operator ^(Matrix A, int deg) //перегруженный оператор возведения матрицы в степень
        {
            if ((A == null) || (deg < 0))
                return null;

            Matrix B = new Matrix(A.size);
            for (int i = 0; i < A.size; i++)
                for (int j = 0; j < A.size; j++)
                    B[i][j] = A[i][j];

            for (int i = 1; i < deg; i++)
                B = B * A;

            return B;
        }

        public void outputInConsole() //вывод элементов матрицы на консоль
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                    System.Console.Write(data[i][j].ToString() + " ");
                System.Console.WriteLine();
            }

            System.Console.WriteLine();
        }
    }

    public class Logic
    {
        static public int sumElementsUpDiagonals(Matrix matrix) //вычисление суммы элементов матрицы, расположенных выше главной диагонали
        {
            int sum = 0;
            for (int i = 0, j = 1; (i < matrix.Size) && (j < matrix.Size); i++, j++)
                for (int k = j; k < matrix.Size; k++)
                    sum += matrix[i][k];
            return sum;
        }

        static public int sumElementsDownDiagonals(Matrix matrix) //вычисление суммы элементов матрицы, расположенных ниже главной диагонали
        {
            int sum = 0;
            for (int i = (matrix.Size - 1), j = (matrix.Size - 2); (i >= 0) && (j >= 0); i--, j--)
                for (int k = j; k >= 0; k--)
                    sum += matrix[i][k];
            return sum;
        }

        static public Matrix getGlobalResult(Matrix A, Matrix B, Matrix C, int T) //Вычисление результирующей матрицы
        {
            if ((A == null) || (B == null) || (C == null)
                || (A.Size != B.Size) || (B.Size != C.Size))
                return null;

            Matrix result = new Matrix(A.Size);

            int sumA = sumElementsDownDiagonals(A) - sumElementsUpDiagonals(A), //разность суммы элементов матрицы А, расположенных ниже главной диагонали
                //и суммы элементов матрицы А, расположенных выше главной диагонали
                sumB = sumElementsDownDiagonals(B) - (-sumElementsUpDiagonals(C)); //разность суммы элементов матрицы В, расположенных ниже главной диагонали
            //и минус суммы элементов матрицы С, расположенных выше главной диагонали

            /*Даны три квадратные матрицы A и B и С
                . Если разность между сумой элементов ниже главной диагонали и суммой элементов выше главной диагонали матрицы A
                 больше чем разность между сумой элементов ниже главной диагонали матрицы B
                 минус сумма элементов выше главной диагонали матрицы C то  (A+C)^T⋅2+B иначе 3⋅B+(A−C)^T
            */

            if (sumA > sumB)
                result = ((A + C) ^ T) * 2 + B;
            else
                result =  3*B + (A - C) ^ T;

            return result;
        }
    }
    class Program
    {
        [DllImport("kernel32.dll")]
        static extern IntPtr GetConsoleWindow();

        [DllImport("user32.dll")]
        static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

        [STAThread]
        static void Main()
        {
            //Блок взаимодействия с пользователем

            //Console Interface: 
            /*int size = 0;
            System.Console.Write("Введите размер матрицы: ");
            while ((!int.TryParse(System.Console.ReadLine(), out size)) || (size <= 0))
                System.Console.Write("Ошибка: введено некорректное число.\nВведите целое число большее 0: ");

            Matrix A = new Matrix(size), B = new Matrix(size), C = new Matrix(size);
            string switchUser = string.Empty;

            System.Console.Write("Ввод данных:\nuser - пользователь вводит данные самостоятельно\nrandom - матрицы заполняются рандомными числами\n\nВыбор: ");
            switchUser = System.Console.ReadLine();
            switchUser = switchUser.Trim();
            while((switchUser != "user") && (switchUser != "random"))
            {
                System.Console.WriteLine("Ошибка: введена не корректная строка, вводить нужно либо user, либо random.");
                System.Console.Write("Ввод данных:\nuser - пользователь вводит данные самостоятельно\nrandom - матрицы заполняются рандомными числами\n\nВыбор: ");
                switchUser = System.Console.ReadLine();
                switchUser = switchUser.Trim();
            }

            if(switchUser == "random")
            {
                
                System.Console.Write("Установка диапазона рандомных чисел:\nuser - пользователь устанавливает диапазон самостоятельно\nstandart - диапазон по умолчанию: [-100; 100]\n\nВыбор: ");
                switchUser = System.Console.ReadLine();
                switchUser = switchUser.Trim();
                while ((switchUser != "user") && (switchUser != "standart"))
                {
                    System.Console.WriteLine("Ошибка: введена не корректная строка, вводить нужно либо user, либо standart.");
                    System.Console.Write("Установка диапазона рандомных чисел:\nuser - пользователь устанавливает диапазон самостоятельно\nstandart - диапазон по умолчанию: [-100; 100]\n\nВыбор: ");
                    switchUser = System.Console.ReadLine();
                    switchUser = switchUser.Trim();
                }

                
                if (switchUser == "user")
                {
                    int min, max;
                    System.Console.Write("Введите значение min: ");
                    while (!int.TryParse(System.Console.ReadLine(), out min))
                        System.Console.Write("Ошибка: введена не корректная строка.\nВведите целое число: ");

                    System.Console.Write("Введите значение max: ");
                    while (!int.TryParse(System.Console.ReadLine(), out max))
                        System.Console.Write("Ошибка: введена не корректная строка.\nВведите целое число: ");

                    A.fillRandom(min, max);
                    B.fillRandom(min, max);
                    C.fillRandom(min, max);
                }
                else
                {
                    A.fillRandom();
                    B.fillRandom();
                    C.fillRandom();
                }
            }
            else
            {
                System.Console.WriteLine("\nМатрица A.\n");
                for(int i = 0; i < A.Size; i++)
                    for(int j = 0; j < A.Size; j++)
                    {
                        System.Console.Write($"Введите элемент ({i} , {j}): ");
                        while (!int.TryParse(System.Console.ReadLine(), out A[i][j]))
                            System.Console.Write("Ошибка: введена не корректная строка.\nВведите целое число: ");
                    }

                System.Console.WriteLine("\nМатрица B.\n");
                for (int i = 0; i < B.Size; i++)
                    for (int j = 0; j < B.Size; j++)
                    {
                        System.Console.Write($"Введите элемент ({i} , {j}): ");
                        while (!int.TryParse(System.Console.ReadLine(), out B[i][j]))
                            System.Console.Write("Ошибка: введена не корректная строка.\nВведите целое число: ");
                    }

                System.Console.WriteLine("\nМатрица C.\n");
                for (int i = 0; i < C.Size; i++)
                    for (int j = 0; j < C.Size; j++)
                    {
                        System.Console.Write($"Введите элемент ({i} , {j}): ");
                        while (!int.TryParse(System.Console.ReadLine(), out C[i][j]))
                            System.Console.Write("Ошибка: введена не корректная строка.\nВведите целое число: ");
                    }
            }

            int T = 0;
            System.Console.WriteLine("\nВведите число T: ");
            while (!int.TryParse(System.Console.ReadLine(), out T))
                System.Console.Write("Ошибка: введена не корректная строка.\nВведите целое число: ");

            System.Console.Clear();

            System.Console.Write("Вывод данных.\n\n");
            System.Console.WriteLine("Матрица A: ");
            A.outputInConsole();

            System.Console.WriteLine("Матрица B: ");
            B.outputInConsole();

            System.Console.WriteLine("Матрица C: ");
            C.outputInConsole();

            Matrix result = Logic.getGlobalResult(A, B, C, T); //запись результирующей матрицы в матрицу result

            System.Console.WriteLine("Матрица, полученная в результате вычислений: ");
            result.outputInConsole();

            System.Console.ReadKey();*/

            ShowWindow(GetConsoleWindow(), 0);
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Window());

            return;
        }
    }
}



