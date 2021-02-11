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
    public class LogicTests
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
            };

        [TestMethod()]
        public void sumElementsUpDiagonalsTest() //Проверка на корректность вычислений суммы элементов матрицы находящиеся выше главной диагонали
        {
            int[] results = new int[5] { 11, 32, 10, 9, -11 };
            for (int i = 0; i < 5; i++)
                Assert.AreEqual(results[i], Logic.sumElementsUpDiagonals(matrix1[i]));
        }

        [TestMethod()]
        public void sumElementsDownDiagonalsTest() //Проверка на корректность вычислений суммы элементов матрицы находящиеся ниже главной диагонали
        {
            int[] results = new int[5] { 19, 22, -1, 12, 29 };
            for (int i = 0; i < 5; i++)
                Assert.AreEqual(results[i], Logic.sumElementsDownDiagonals(matrix1[i]));
        }

    }
}