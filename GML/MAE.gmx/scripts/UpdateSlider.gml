///UpdateSlider(slider);
sldr[argument0, sliderval.value] = clamp(sldr[argument0, sliderval.value], sldr[argument0, sliderval.mmin], sldr[argument0, sliderval.mmax]);
return sldr[argument0, sliderval.value];
