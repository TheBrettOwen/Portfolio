function [scores, result_image] = skin_chamfer_search(color_image, pos, neg, edge_image, template, scale, number_of_results) 

%images
edge_image = read_gray(edge_image);
color_image = imread(color_image);

color_image = detect_skin(color_image, pos, neg);
color_image = color_image > 0.5;
image = edge_image & color_image;

%template
template = read_gray(template);
template = template>0; 
[temprows, tempcols] = size(template);

%resize to specified scale
resized = imresize(image, scale, 'bilinear');
resized_dt = bwdist(resized);
scores = imfilter(resized_dt, double(template), 'symmetric');

%normalize scores, then give 1 the bottom 100 scores in scores
scores = scores / max(max(scores));
a = scores(:);
a = mink(a, number_of_results * 10);

finalpoints = zeros(size(scores));
counter = size(a)/number_of_results; 

%for every number in a, 
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
