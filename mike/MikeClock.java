/*    
 *  Digital Clock Java applet  06/27/96
 *    by Mike Perham mperham@cs.cornell.edu
 *
 *  Blinks the colon every second; refreshes time
 *  every minute.  Futuristic LED display.  Generally nifty.
 *
 *  Array digit[] holds a bitmask of which LEDs each number
 *  lights up: digit[1] = 6 because it lights up the 2nd
 *  and 3rd LEDs.
 *            1
 *          ------
 *         7| 6  |2
 *          ------
 *         5|    |3
 *          ------
 *            4
 *
 *    Each digit is drawn using the x[] and y[] coords.  The
 *    graphics coordinate-space is translated so that even though
 *    they are the same coords each time, they are drawn in a 
 *    different position.  This makes the digits much easier to
 *    synchronize (they are all the same size) and move.
 *
 * v1.01 - 7/18/96 - Changed first digit to a simple "1" to
 *         save space and improve look.
 *    
 * v1.02 - 3/16/97 - Updated to 1.1 API.  Rewrote a few lines
 * 			to lower memory usage now that I know Java much better.
 *
 * v1.03 - 2/6/99  - Fixed two small bugs and cleaned up code.
 */    

import java.awt.*;
import java.util.*;
import java.applet.*;

public final class MikeClock extends Applet implements Runnable 
{
    final static int[] digit = { 95, 6, 59, 47, 102, 109, 125, 7, 127, 103 };
    final static int size_x = 149;
	final static int size_y = 52;
    final static int digit_width = 31;
	final static int space = 5;
    final static int border = 6;
	
    boolean blink_on = false;
    Thread clockThread;
    Graphics g, h;
    int secs;
	
	/*
	 * X coordinates for all the points in the '8' character.
	 * There are 7 segments with 6 points each.
	 */
    int[][] x = 
	{
		{  5,  8, 23, 26, 23,  8 },
		{ 28, 31, 31, 28, 25, 25 },
		{ 28, 31, 31, 28, 25, 25 },
		{  5,  8, 23, 26, 23,  8 },
		{  3,  6,  6,  3,  0,  0 },
		{  5,  8, 23, 26, 23,  8 },
		{  3,  6,  6,  3,  0,  0 } 
    };
                  
	/*
	 * Y coordinates for all the points in the '8' character.
	 */
    int[][] y = 
	{
		{  3,  0,  0,  3,  6,  6 },
		{  5,  8, 18, 21, 18,  8 },
		{ 24, 27, 37, 40, 37, 27 },
		{ 41, 38, 38, 41, 44, 44 },
		{ 24, 27, 37, 40, 37, 27 },
		{ 23, 20, 20, 23, 26, 26 },
		{  5,  8, 18, 21, 18,  8 }
    };

    /*
	 * Coordinates for the first digit since it only needs to display 1 
	 */
    int[][] firstx = 
	{
		{ 5, 8, 8, 5, 2, 2 },
		{ 5, 8, 8, 5, 2, 2 }
    };
         
    int[][] firsty = 
	{
        {  5,  8, 18, 21, 18,  8 },
        { 24, 27, 37, 40, 37, 27 }
    };
         
    public void start() 
	{
		g = getGraphics();
        setBackground(Color.black);
        clockThread = new Thread(this, "Clock");
        clockThread.start();
    }

    public void stop() 
	{
		clockThread.stop();
		clockThread = null;
    }

	/*
	 * This is the Clock thread's main loop.
	 */
    public void run()
	{	
		secs = Calendar.getInstance().get(Calendar.SECOND);
		
    	while (clockThread != null)
		{
			if (secs < 59) 
			{
				secs++;
			} 
			else 
			{
				secs = Calendar.getInstance().get(Calendar.SECOND);
				paint(g);
			}
			blink();
			try 
			{
				clockThread.sleep(1000);
			} catch (InterruptedException e) {}
		}
    }
    
    public void paint(Graphics gr) 
	{
        draw_time();
        draw_border();
    }
	
	/************************************
	 * Drawing implementation
	 */

	void blink() 
	{
        if (blink_on) 
		{
            g.setColor(Color.cyan);
        } 
		else 
		{
            g.setColor(Color.darkGray);
        }
        blink_on = !blink_on;    
        g.fillOval(digit_width*2+border+space*2+5 - 23, 20, 5, 5);
        g.fillOval(digit_width*2+border+space*2+5 - 23, 35, 5, 5);
    }

    void draw_digit(int num, boolean bFirstDigit)
	{
        int mask = 1;
            
		/**
		 * Special case the first digit
		 */
        if (bFirstDigit)
		{
            if (num == 1) 
			{
            	h.setColor(Color.cyan);
            } 
			else 
			{
            	h.setColor(Color.black);
            }
             h.fillPolygon(firstx[0], firsty[0], 6);
             h.fillPolygon(firstx[1], firsty[1], 6);
        } 
		else 
		{
			for (int i = 0; i < 7; i++) 
			{
				if ((digit[num] & mask) != 0) 
				{
					h.setColor(Color.cyan);
				} 
				else 
				{
					h.setColor(Color.darkGray);        
				}
				h.fillPolygon(x[i], y[i], 6);
				mask <<= 1;
			}
		}
    }
        
    void draw_time() 
	{
        int min = Calendar.getInstance().get(Calendar.MINUTE);
        int hours = Calendar.getInstance().get(Calendar.HOUR);
        int m1, m2, h1, h2;
        
        if (hours > 12) 
		{
        	hours -= 12;
        }
		if (hours == 0) 
		{
			hours = 12;
		}
        h1 = hours/10;
        h2 = hours%10;
        m1 = min/10;
        m2 = min%10;
        
        /* 
         * Make a copy of the graphics space so that the
         * translations are only temporary.
         */    
        h = g.create();
        h.translate(border+space, border+space-1);
        draw_digit(h1, true);
        h.translate(8 + space, 0);
        draw_digit(h2, false);
        h.translate(digit_width + space + 10, 0);
        draw_digit(m1, false);
        h.translate(digit_width + space, 0);
        draw_digit(m2, false);
        h = null;
    }

    void draw_border() 
	{
		g.setColor(Color.lightGray);
        g.fill3DRect(0, 0, size_x, border, true);
        g.fill3DRect(size_x-border, border, border, size_y, true);
        g.fill3DRect(0, size_y+border, size_x, border, true);
        g.fill3DRect(0, border, border, size_y, true);
    }
}
