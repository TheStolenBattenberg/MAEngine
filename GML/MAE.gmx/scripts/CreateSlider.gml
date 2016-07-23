///CreateSlider(min, max, default);
enum sliderval {
    value,
    mmin,
    mmax
}

sldr[sldrs, sliderval.value] = argument2;
sldr[sldrs, sliderval.mmin]  = argument0;
sldr[sldrs, sliderval.mmax]  = argument1;
sldrs++;
return sldrs-1;