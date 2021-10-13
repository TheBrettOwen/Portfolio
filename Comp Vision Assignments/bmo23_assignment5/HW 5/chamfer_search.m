function [scores, result_image] = chamfer_search(edge_image, template, scale, number_of_results)

%image
image = read_gray(edge_image);
image = image > 0; 

%template
template = read_gray(template);
template = template>0; 
[temprows, tempcols] = size(template);

resized = imresize(image, scale, 'bilinear');
resized_dt = bwdist(resized);
scores = imfilter(resized_dt, double(template), 'symmetric');

scores = scores / max(max(scores));

a = scores(:);
a = mink(a, number_of_results * 100); 

finalpoints = zeros(size(scores));
counter = size(a)/number_of_results; 

for c = 1:length(a)
    [rows, cols] = find( scores == a(c));
    finalpoints(rows,cols) = a(c);
        
    if mod(c, counter) == 0
        image = draw_rectangle2(image, rows, cols, temprows, tempcols);
    end
end 

scores = finalpoints;
result_image = image;
end