export module Sandcore.Graphics.Image.Gradient;

import Sandcore.Graphics.Image;

export namespace Sandcore::Graphics {
	Pixel gradient(Pixel a, Pixel b, float c) {
		float sr = a.r * (1 - c) + b.r * c;
		float sg = a.g * (1 - c) + b.g * c;
		float sb = a.b * (1 - c) + b.b * c;
		float sa = a.a * (1 - c) + b.a * c;

		if (sr > 255) sr = 255;
		if (sg > 255) sg = 255;
		if (sb > 255) sb = 255;
		if (sa > 255) sa = 255;

		return Pixel(sr, sg, sb, sa);
	}
}