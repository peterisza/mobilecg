/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Peter Isza, Robert Csordas
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
