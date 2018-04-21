using Sbatman.Serialize;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;

namespace AssetPacker
{
    internal class Program
    {
        private const string INPUTFOLDER = "Input";
        private const string OUTPUTFOLDER = "Output";
        private const UInt16 PACKETID_PACK = 1412;
        private const UInt16 PACKETID_PNG = 1247;

        private static void Main(string[] args)
        {
            if (!Directory.Exists(INPUTFOLDER)) { Console.WriteLine("Input Folder Missing"); return; }
            if (!Directory.Exists(OUTPUTFOLDER)) Directory.CreateDirectory(OUTPUTFOLDER);

            List<string> DetectedFiles = new List<string>();

            DetectFiles(DetectedFiles, INPUTFOLDER);

            FilterFiles(ref DetectedFiles);

            List<Tuple<string, Packet>> ProcessedFiles = new List<Tuple<string, Packet>>();

            foreach (string s in DetectedFiles)
            {
                if (s.ToLowerInvariant().EndsWith(".png")) ProcessedFiles.Add(ProcessPNG(s));
            }

            foreach (Tuple<string, Packet> p in ProcessedFiles)
            {
                byte[] packData = p.Item2.ToByteArray();
                string outputFile = OUTPUTFOLDER + "\\" + p.Item1;
                CheckCreateOutputDirectory(outputFile);
                using (FileStream outStream = File.Create(outputFile))
                {
                    outStream.Write(packData, 0, packData.Length);
                }
                p.Item2.Dispose();
            }

            ProcessedFiles.Clear();
        }

        /// <summary>Will check to see if the directory the output file is located in exists, if it doesn't then it will create it</summary>
        /// <param name="outputFile"></param>
        /// <returns>true if the directory was created</returns>
        private static bool CheckCreateOutputDirectory(String outputFile)
        {
            outputFile = outputFile.Replace("/", "\\");

            string[] temp = outputFile.Split('\\');

            string outputFolder = "";
            int max = temp.Length - 1;

            for (int i = 0; i < max; i++)
            {
                outputFolder += temp[i];
                if (i < max) outputFolder += "\\";
            }

            if (!Directory.Exists(outputFolder))
            {
                Directory.CreateDirectory(outputFolder);
                return true;
            }

            return false;
        }

        private static void FilterFiles(ref List<string> detectedFiles)
        {
            detectedFiles = detectedFiles.Where(s => s.ToLowerInvariant().EndsWith(".png")).ToList();
        }

        private static void DetectFiles(List<string> detectedFiles, string folder)
        {
            detectedFiles.AddRange(Directory.EnumerateFiles(folder));
            foreach (string s in Directory.EnumerateDirectories(folder)) DetectFiles(detectedFiles, s);
        }

        private static Tuple<Int32, Int32, byte[], string> LoadPng(string fileName)
        {
            using (Bitmap bmp = new Bitmap(fileName))
            {
                int bytes = bmp.Width * bmp.Height * 4;

                byte[] returnData = new byte[bytes];
                BitmapData dat = bmp.LockBits(new Rectangle(0, 0, bmp.Width, bmp.Height), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);
                IntPtr ptr = dat.Scan0;
                Marshal.Copy(ptr, returnData, 0, bytes);

                return new Tuple<int, int, byte[], string>(bmp.Width, bmp.Height, returnData, fileName);
            }
        }

        private static Tuple<string, Packet> ProcessPNG(string fileName)
        {
            Tuple<int, int, byte[], string> data = LoadPng(fileName);
            Packet p = new Packet(PACKETID_PNG);
            p.Add(data.Item1);
            p.Add(data.Item2);
            p.Add(data.Item3);
            return new Tuple<string, Packet>(fileName.Replace(INPUTFOLDER + "\\", "").ToLower().Replace(".png", ".Gdat"), p);
        }
    }
}