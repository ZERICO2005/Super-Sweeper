import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import javax.swing.*;
import java.lang.Object.*;
import java.io.OutputStream.*;
 
public class Engine {
    
	static int pSize = 16; //Palette Size
	
	static int resX = 168;
	static int resY = 126;
	static int frames = 84;
	static int[] video = new int[resX * resY * frames];
	static int[] color = new int[pSize * frames];
	static int iX = 168;
	static int iY = 126;
	static int[] image = new int[iX * iY * 3];
	
	static int[] colorR = new int[pSize * frames];
	static int[] colorG = new int[pSize * frames];
	static int[] colorB = new int[pSize * frames];
	
	static int frame = 0;
	
	static int[] count = new int[32769]; //32768 is null
	static int[] rank = new int[pSize];
	static int[] order = new int[pSize];
	
	static int limit = 3; //1: 15bit, 2: 12bit, 4: 9bit, 8: 6bit
	static int[] bin = new int[pSize];
	
	static String[] huffCode = {"00","010","011","10000","10001","1001","101","110000","1100010","1100011","110010","110011","11010","110110","110111","111"};
	
	public static void makeColor() {
		
		int[] temp = new int[pSize];
		for (int i = 0; i < 32768; i++) {
			count[i] = 0;
		}
		for (int i = 0; i < iX * iY; i++) { //Counts each color present, limit reduces the bit depth to improve results
				int r = (image[3 * i] / 8) / limit * limit; //Converts to 15bit then reduces bit depth
				int g = (image[3 * i + 1] / 8) / limit * limit;
				int b = (image[3 * i + 2] / 8) / limit * limit;
				int c = (r * 1024) + (g * 32) + b;
				count[c]++;
		}
		
		for (int j = 0; j < pSize; j++) {
			temp[j] = 32768; //32768 doesn't exist
		}
		
		temp[0] = 0; //Hard-coded black
		count[0] = 65535; //pSize - 1
		

		
		for (int i = 1; i < 32768; i++) { //Loops through all colors except black
			if ((i == 28672 || i == 29568) && (frame >= 23 && frame <= 61)) {
				i++;
			}
			if (count[i] != 0) { //Check that the color still exists
				//int low = 65536;
				for (int j = 0; j < pSize; j++) { //Runs through the leaderboard of colors
					if (count[i] > count[temp[j]] && colorDistance(i,j)) {
						temp[j] = i;
						break;
					}
				}
			}
		}
		
//		if (frame >= 0 && frame <= 77) {
//			temp[15] = 0;
//		}
		//temp[15] = 0;
		if (frame >= 25 && frame <= 61) {
			temp[15] = 28672; //Red
			temp[14] = 29568; //Yellow
		}
//		if (frame >= 0 && frame <= 62) {
//			temp[15] = 0;
//		}
//		if (frame >= 23 && frame <= 61) {
//			temp[14] = 28672; //Red
//			temp[13] = 29568; //Yellow
//		}

		for (int i = 0; i < pSize; i++) {
			int c = temp[i];
			color[i + (frame * pSize)] = c;
			colorR[i + (frame * pSize)] = (c / 1024) * 8;
			colorG[i + (frame * pSize)] = ((c / 32) % 32) * 8;
			colorB[i + (frame * pSize)] = (c % 32) * 8;
			//System.out.println(c);
		}
	}
	
   public static boolean colorDistance(int c, int d) {
		float r0 = (float)((c / 1024) * 8);
        float g0 = (float)(((c / 32) % 32) * 8);
        float b0 = (float)((c % 32) * 8);
        
		float r1 = (float)((d / 1024) * 8);
        float g1 = (float)(((d / 32) % 32) * 8);
        float b1 = (float)((d % 32) * 8);
        float distance = (float) Math.sqrt( (r1-r0)*(r1-r0) + (g1-g0)*(g1-g0) + (b1-b0)*(b1-b0) );
        if (distance < 36) { //36
        	return false;
        } else {
        	return true;
        }
    }
   
	public static void main(String[] args) {
    	egaColor();
    	
    	for (frame = 0; frame < frames; frame++) {
        	loadImage(frame + 0);
        	makeColor();
			float xR = (float)iX / (float)resX;
			float yR = (float)iY / (float)resY;
			int oV = frame * resX * resY;
        	for (int y = 0; y < resY; y++) {
				for (int x = 0; x < resX; x++) {
		        	int u = (int)((float)x * xR);
		        	int v = (int)((float)y * yR);
					video[(y * resX) + x + oV] = findColor(3 * (v * iX + u));
				}
			}
        	System.out.println("Frame: " + frame);
        	imageIoWrite();
    	}
    	//huffMan();
    	export();
    }
	
   public static void export() {

	   try {
		   
           int blocks = ((resX * resY / 2) * frames) / 65536;
           if (blocks % 65536 != 0) {blocks++;} //Ceiling Function
           int i = 0;
           
    	   for (int f = 0; f < blocks; f++) {
               OutputStream out = new FileOutputStream("video-" + String.format("%02d", f) + ".bin");
        	   for (int j = 0; j < resX * resY * 6 / 2; j++) {
        		   out.write(((video[i + 1] << 4) + video[i]));
//        		   if (video[i + 1] > 8 && video[i] > 8) {
//            		   System.out.println();
//            		   System.out.println((video[i + 1] << 4) + video[i]);
//            		   System.out.println(video[i + 1] << 4);
//            		   System.out.println(video[i]);
//        		   }
        		   i += 2;
        	   }
               out.close();
    	   }
    	   
    	   System.out.println();
    	   for (int f = 0; f < blocks; f++) {
    		   System.out.println("convbin --archive --input \"C:\\Users\\zerico\\Eclispe Java\\Video Convert\\video-" + String.format("%02d", f) + ".bin\" --output \"C:\\Users\\zerico\\Documents\\FOO\\video-" + String.format("%02d", f) + ".8xv\" --iformat bin --oformat 8xv --name VOD" + String.format("%02d", f));
    	   }
//           int blocks = ((resX * resY / 2) * frames) / 65536;
//           if (blocks % 65536 != 0) {blocks++;}
//    	   for (int f = 0; f < blocks; f++) {
//               Writer out = new FileWriter("video-" + f + ".txt");
//               out.write("unsigned char data[" + (resX * resY * frames / 2 / blocks) + "] = {" + ((video[1] << 4) + video[0]));
//        	   for (int i = 2 + f * (resX * resY * frames / blocks); i < (f + 1) *(resX * resY * frames / blocks); i += 2) {
//        		   out.write("," + ((video[i + 1] << 4) + video[i]));
//        	   }
//        	   out.write("};");
//               out.close();
//    	   }
    	   
//           out.write("unsigned char data[" + (resX * resY * frames / 2) + "] = {" + ((video[1] << 4) + video[0]));
//    	   for (int i = 2; i < resX * resY * frames; i += 2) {
//    		   out.write("," + ((video[i + 1] << 4) + video[i]));
//    	   }
//           out.write("unsigned int data[" + (resX * resY * frames / 6) + "] = {" + ((video[5] << 20) + (video[4] << 16) + (video[3] << 12) + (video[2] << 8) + (video[1] << 4) + video[0]));
//    	   for (int i = 6; i < resX * resY * frames; i += 6) {
//    		   out.write("," + ((video[i + 5] << 20) + (video[i + 4] << 16) + (video[i + 3] << 12) + (video[i + 2] << 8) + (video[i + 1] << 4) + video[i]));
//    	   }
//    	   out.write("};");
    	   
    	   System.out.println("\nFinished Video");

           } catch (Exception e) {
           e.getStackTrace();
 
           }
   	   for (int f = 0; f < 15; f++) { //debug start
		   System.out.println("convbin --archive --input \"C:\\Users\\zerico\\Eclispe Java\\Video Convert\\video-" + String.format("%02d", f) + ".bin\" --output \"C:\\Users\\zerico\\Documents\\FOO\\video-" + String.format("%02d", f) + ".8xv\" --iformat bin --oformat 8xv --name VOD" + String.format("%02d", f));
	   } //debug end
	   try {
           Writer out = new FileWriter("color.txt");
    	   
           //out.write("unsigned short palette[" + (pSize * frames) + "] = {/*0*/" + color[0]);
           out.write("unsigned short palette[" + ((pSize - 1) * frames) + "] = {/*0*/"); //If skipping black
    	   for (int i = 1; i < pSize * frames; i++) {
//    		   if (i % 16 == 0) {
//    			   out.write("/*" + (i/16) + "*/");
//    		   }
//    		   out.write("," + color[i]);
    		   if (i % 16 == 0) { //If skipping black
    			   out.write("/*" + (i/16) + "*/");
    		   } else {
    			   out.write("," + color[i]);
    		   }
    	   }
    	   out.write("};");
    	   
    	   System.out.println("\nFinished Palette");

           out.close();
       } catch (Exception e) {
           e.getStackTrace();
       }
	   
   }
   
   public static void huffMan() {
	   System.out.println("\nColor Count:\n");
	   for (int i = 0; i < pSize; i++) {
		   rank[i] = 0;
		   order[i] = i;
	   }
	   for (int i = 0; i < resX * resY * frames; i++) {
		   rank[video[i]]++;
	   }
	   //bubbleSort();
	   for (int i = 0; i < pSize; i++) {
		   System.out.println(rank[i] + " " + order[i]);
	   }
	   System.out.println("\nOriginal Bytes: " + (resX * resY * frames / 2));
	   
	   int[] sum = new int[pSize];
	   int[] node0 = new int[pSize];
	   int[] node1 = new int[pSize];
	   
	   int[][] value = new int[pSize][pSize + 1];
	   
	   for (int i = 0; i < pSize; i++) {
		   value[i][pSize] = order[i];
	   }
	   for (int i = 0; i < pSize; i++) {
		   value[i][pSize] = order[i];
	   }
//	   if (rank[i] < low[]) {
//		   low[] = rank[i];
//	   }
//	   System.out.println(rank[i]);
	   System.out.print("\nint n = " + pSize);
	   System.out.print("\nchar[] charArray = {" + order[0]);
	   for (int i = 1; i < pSize; i++) {
		   System.out.print("," + order[i]);
	   }
	   System.out.print("};");
	   System.out.print("\nint[] charfreq = {" + rank[0]);
	   for (int i = 1; i < pSize; i++) {
		   System.out.print("," + rank[i]);
	   }
	   System.out.print("};\n\n");
	   
	   for (int i = 0; i < huffCode.length; i++) {
		   //System.out.println(huffCode[i]);
		   bin[i] = 0;
		   for (int j = 0; j < huffCode[i].length(); j++) {
			   bin[i] = bin[i] * 2;
			   if (huffCode[i].charAt(j) == '1') {
				   bin[i]++;
			   }
		   }
	   }
	   
	   for (int i = 0; i < huffCode.length; i++) {
		   int bin = 0;
		   for (int j = 0; j < huffCode[i].length(); j++) {
			   bin = bin * 2;
			   if (huffCode[i].charAt(j) == '1') {
				   bin++;
			   }
		   }
		   System.out.println(bin);
	   }
   }
   
   public static void bubbleSort() {
       int n = pSize;
       for (int i = 0; i < n; i++) {
           for (int j = 0; j < n - 1; j++) {
               if (rank[j] > rank[j + 1]) {
                   int t = rank[j];
                   int p = order[j];
                   rank[j] = rank[j + 1];
                   order[j] = order[j + 1];
                   rank[j + 1] = t;
                   order[j + 1] = p;
               }
           }
       }
   }
   
   public static void bubSort() {
       int n = pSize;
       for (int i = 0; i < n; i++) {
           for (int j = 0; j < n - 1; j++) {
               if (order[j] > order[j + 1]) {
                   int t = rank[j];
                   int p = order[j];
                   rank[j] = rank[j + 1];
                   order[j] = order[j + 1];
                   rank[j + 1] = t;
                   order[j + 1] = p;
               }
           }
       }
   }
   
   
    
    public static int compareColor(int c) {
		float r0 = (float)((c / 1024) * 8);
        float g0 = (float)(((c / 32) % 32) * 8);
        float b0 = (float)((c % 32) * 8);
    	int best = 0;
    	float score = 65535;
    	for (int i = 0; i < 32768; i++) {
    		if (count[i] != 0) {
        		float r1 = (float)((i / 1024) * 8);
                float g1 = (float)(((i / 32) % 32) * 8);
                float b1 = (float)((i % 32) * 8);
                float distance = (float) Math.sqrt( (r1-r0)*(r1-r0) + (g1-g0)*(g1-g0) + (b1-b0)*(b1-b0) );
                if (distance < score) {
                	best = i;
                	score = distance;
                }
    		}
    	}
		return best;
    }
    
    public static int findColor(int index) {
		float r0 = (float)image[index];
        float g0 = (float)image[index + 1];
        float b0 = (float)image[index + 2];
    	int best = 0;
    	float score = 65535;
    	for (int i = 0; i < pSize; i++) {
    		float r1 = (float)colorR[frame * pSize + i];
            float g1 = (float)colorG[frame * pSize + i];
            float b1 = (float)colorB[frame * pSize + i];
            float distance = (float) Math.sqrt( (r1-r0)*(r1-r0) + (g1-g0)*(g1-g0) + (b1-b0)*(b1-b0) );
            if (distance < score) {
            	best = i;
            	score = distance;
            }
    	}
		return best;
    }
    
    public static int colorP(int index) {
		return 0;
    }
    
	private static void loadImage(int i) {
		try {
			//File file = new File("E:\\Coding\\Fractal Video 0\\Frame " + (i * 5) + ".png");
			File file = new File("E:\\Youtube\\MineSweeper\\PNG Video 126p\\Frame-" + String.format("%03d", i) + ".png");
			BufferedImage bufferedImage = ImageIO.read(file);
			for (int y = 0; y < iY; y++) {
				for (int x = 0; x < iX; x++) {
					Color c = new Color(bufferedImage.getRGB(x,y));
					image[3 * (y * iX + x)] = c.getRed();
					image[3 * (y * iX + x) + 1] = c.getGreen();
					image[3 * (y * iX + x) + 2] = c.getBlue();
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void imageIoWrite() {
		try {
			int e = 0;
			int g = 0;
			int b = 0;

			BufferedImage img;
			
			int oV = frame * resX * resY;
			img = new BufferedImage(resX, resY, BufferedImage.TYPE_INT_RGB);
			for (int y = 0; y < resY; y++) {
				for (int x = 0; x < resX; x++) {
					e = colorR[frame * pSize + video[oV + ((y * resX) + x)]];
					g = colorG[frame * pSize + video[oV + ((y * resX) + x)]];
					b = colorB[frame * pSize + video[oV + ((y * resX) + x)]];
					int color = (e << 16) | (g << 8) | b;
					img.setRGB(x, y, color);
				}
			}
			
			if (frames > 1) {
				ImageIO.write(img, "PNG", new File("E:\\Youtube\\MineSweeper\\Calculator 126p\\Frame-" + frame + ".png"));
			} else {
				ImageIO.write(img, "PNG", new File("E:\\Youtube\\MineSweeper\\Calculator 126p\\Frame-" + System.nanoTime() + ".png"));
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
 	public static void egaColor() {
		int[] ega = { 0, 31744, 32736, 992, 1023, 31, 31775, 32767, 7399, 15360, 15840, 480, 495, 15, 15375, 24311 };
 		//int[] ega = { 0x0000, 0x0842, 0x1084, 0x18C6, 0x2108,  0x294A, 0x318C, 0x39CE, 0x4210, 0x4A5, 0x4E93, 0xD6B5, 0xDEF7, 0xE739, 0xEF7B, 0xF7BD}; //Greyscale
		for (int i = 0; i < pSize * frames; i++) {
			color[i] = ega[i%pSize];
			colorR[i] = (color[i%pSize] / 1024) * 8;
			colorG[i] = ((color[i%pSize] / 32) % 32) * 8;
			colorB[i] = (color[i%pSize] % 32) * 8;
		}
//		for (int i = 0; i < pSize * frames; i++) {
//			int foo = (int)(Math.random() * 32768);
//			color[i] = foo;
//			colorR[i] = (foo / 1024) * 8;
//			colorG[i] = ((foo / 32) % 32) * 8;
//			colorB[i] = (foo % 32) * 8;
//		}
	}
 	public static void printColor(int i) {
 		System.out.print("\n" + String.format("%05d",i));
 		System.out.print(" ");
 		System.out.print(String.format("%03d",((i / 1024) * 8)));
 		System.out.print(" ");
 		System.out.print(String.format("%03d",(((i / 32) % 32) * 8)));
 		System.out.print(" ");
 		System.out.print(String.format("%03d",(i % 32) * 8));
 	}
}
