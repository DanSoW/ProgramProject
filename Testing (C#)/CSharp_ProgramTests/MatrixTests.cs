using Microsoft.VisualStudio.TestTools.UnitTesting;
using CSharp_Program;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp_Program.Tests
{
    [TestClass()]
    public class MatrixTests
    {
        public Matrix[] matrix1 = new Matrix[5] //Данные для тестирования
            {
                new Matrix(new int[3][]
                {
                    new int[3]{1, 2, 3},
                    new int[3]{4, 5, 6},
                    new int[3]{7, 8, 9}
                }),
                 new Matrix(new int[3][]
                {
                    new int[3]{5, 8, 11},
                    new int[3]{4, 1, 13},
                    new int[3]{9, 9, 9}
                }),
                  new Matrix(new int[3][]
                {
                    new int[3]{5, 5, 1},
                    new int[3]{-2, -3, 4},
                    new int[3]{-2, 3, 3}
                }),
                   new Matrix(new int[3][]
                {
                    new int[3]{3, 4, 4},
                    new int[3]{10, 9, 1},
                    new int[3]{1, 1, 0}
                }),
                    new Matrix(new int[3][]
                {
                    new int[3]{-1, -2, -3},
                    new int[3]{4, 5, -6},
                    new int[3]{7, 18, 9}
                })
            },

            matrix2 = new Matrix[5]
            {
                new Matrix(new int[3][]
                {
                    new int[3]{1, 2, 3},
                    new int[3]{4, 5, 6},
                    new int[3]{7, 8, 9}
                }),
                 new Matrix(new int[3][]
                {
                    new int[3]{5, 0, 11},
                    new int[3]{4, 1, 13},
                    new int[3]{9, 9, 9}
                }),
                  new Matrix(new int[3][]
                {
                    new int[3]{5, 5, 1},
                    new int[3]{-2, -3, 4},
                    new int[3]{-2, 3, 3}
                }),
                   new Matrix(new int[3][]
                {
                    new int[3]{3, 4, 4},
                    new int[3]{10, -90, 1},
                    new int[3]{1, 1, 0}
                }),
                    new Matrix(new int[3][]
                {
                    new int[3]{-1, -2, -3},
                    new int[3]{4, 5, -6},
                    new int[3]{7, 18, 9}
                })
            };

        [TestMethod()]
        public void TestEquallyFunction() //Проверка на корректное выполнение статической функции matrixEquallyMatrix
        {
            bool[] results = new bool[5]
            {
                true,
                false,
                true,
                false,
                true
            };

            for (int i = 0; i < 5; i++)
                Assert.AreEqual(results[i], Matrix.matrixEquallyMatrix(matrix1[i], matrix2[i]));
        }

        [TestMethod()]
        public void TestSumMatrix() //Проверка операций +, - для матриц
        {
            Matrix[] matrixResults = new Matrix[5]
            {
                new Matrix(new int[3][]
                {
                    new int[3]{2, 4, 6},
                    new int[3]{8, 10, 12},
                    new int[3]{14, 16, 18}
                }),
                new Matrix(new int[3][]
                {
                    new int[3]{0, 8, 0},
                    new int[3]{0, 0, 0},
                    new int[3]{0, 0, 0}
                }),
                new Matrix(new int[3][]
                {
                    new int[3]{10, 10, 2},
                    new int[3]{-4, -6, 8},
                    new int[3]{-4, 6, 6}
                }),
                new Matrix(new int[3][]
                {
                    new int[3]{8, 4, 4},
                    new int[3]{10, 14, 1},
                    new int[3]{1, 1, 5}
                }),
                new Matrix(new int[3][]
                {
                    new int[3]{-9, -2, -3},
                    new int[3]{4, -3, -6},
                    new int[3]{7, 18, 1}
                })
            };

            int[] numbers = new int[2] { 5, 8 };

            bool[] results = new bool[5]
            {
                Matrix.matrixEquallyMatrix(matrixResults[0], (matrix1[0] + matrix2[0])),
                Matrix.matrixEquallyMatrix(matrixResults[1], (matrix1[1] - matrix2[1])),
                Matrix.matrixEquallyMatrix(matrixResults[2], (matrix2[2] + matrix1[2])),
                Matrix.matrixEquallyMatrix(matrixResults[3], (matrix1[3] + numbers[0])),
                Matrix.matrixEquallyMatrix(matrixResults[4], (matrix1[4] - numbers[1]))
            };

            for (int i = 0; i < 5; i++)
                Assert.AreEqual(true, results[i]);
        }

        [TestMethod()]
        public void TestMultiplicationMatrix() //Проверка корректного умножения матриц на другие матрицы и числа
        {
            Matrix[] matrixResults = new Matrix[5]
            {
                new Matrix(new int[3][]
                {
                    new int[3]{30, 36, 42},
                    new int[3]{66, 81, 96},
                    new int[3]{102, 126, 150}
                }),
                 new Matrix(new int[3][]
                {
                    new int[3]{156, 107, 258},
                    new int[3]{141, 118, 174},
                    new int[3]{162, 90, 297}
                }),
                  new Matrix(new int[3][]
                {
                    new int[3]{13, 13, 28},
                    new int[3]{-12, 11, -2},
                    new int[3]{-22, -10, 19}
                }),
                   new Matrix(new int[3][]
                {
                    new int[3]{-15, -20, -20},
                    new int[3]{-50, -45, -5},
                    new int[3]{-5, -5, 0}
                }),
                    new Matrix(new int[3][]
                {
                    new int[3]{-4, -8, -12},
                    new int[3]{16, 20, -24},
                    new int[3]{28, 72, 36}
                })
            };

            int[] numbers = new int[2] { -5, 4 };

            for (int i = 0; i < 3; i++) //Проверка матриц умноженных на матрицы
                Assert.AreEqual(true, Matrix.matrixEquallyMatrix(matrixResults[i], matrix1[i] * matrix2[i]));
            for (int i = 3; i < 5; i++)
                Assert.AreEqual(true, Matrix.matrixEquallyMatrix(matrixResults[i], matrix1[i] * numbers[(i-3)]));
        }

        [TestMethod()]
        public void TestPowMatrix() //Проверка на корректное возведение в степень матрицы
        {
            Matrix[] matrixResults = new Matrix[5]
            {
                new Matrix(new int[3][]
                {
                    new int[3]{1, 2, 3},
                    new int[3]{4, 5, 6},
                    new int[3]{7, 8, 9}
                }),
                 new Matrix(new int[3][]
                {
                    new int[3]{156, 147, 258},
                    new int[3]{141, 150, 174},
                    new int[3]{162, 162, 297}
                }),
                  new Matrix(new int[3][]
                {
                    new int[3]{-17, 110, 149},
                    new int[3]{-78, -99, 26},
                    new int[3]{-128, -23, -5}
                }),
                   new Matrix(new int[3][]
                {
                    new int[3]{9309, 9308, 3476},
                    new int[3]{21812, 21813, 8159},
                    new int[3]{2327, 2327, 870}
                }),
                    new Matrix(new int[3][]
                {
                    new int[3]{65276, 144442, 32064},
                    new int[3]{52966, 199421, 228216},
                    new int[3]{-302716, -570698, 95136}
                })
            };

            int[] numbers = new int[5] { 1, 2, 3, 4, 5 };

            for (int i = 0; i < 5; i++)
                Assert.AreEqual(true, Matrix.matrixEquallyMatrix(matrixResults[i], matrix1[i] ^ numbers[i]));
        }
    }
}