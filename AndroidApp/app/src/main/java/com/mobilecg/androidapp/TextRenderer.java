package com.mobilecg.androidapp;

import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.graphics.Canvas;

import java.nio.ByteBuffer;

public class TextRenderer {
    public TextRenderer() {
        paint = new Paint();

        paint.setTextAlign(Paint.Align.LEFT);
        paint.setTypeface(Typeface.SANS_SERIF);
        paint.setAntiAlias(true);
        paint.setTextSize(10);
        paint.setColor(Color.BLACK);
    }

    public void setText(String itext, int size, int color) {
        text = itext;
        paint.setTextSize(size);
        paint.setColor(color);
        baseline = -paint.ascent(); // ascent() is negative
        width = (int) (paint.measureText(text) + 0.5f); // round
        height = (int) (baseline + paint.descent() + 0.5f);
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public void renderToBitmap(byte[] buffer) {
        Bitmap image = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(image);
        canvas.drawText(text, 0, baseline, paint);
        image.copyPixelsToBuffer(ByteBuffer.wrap(buffer));
    }

    private String text;
    private int width;
    private int height;
    private float baseline;
    private Paint paint;
}
