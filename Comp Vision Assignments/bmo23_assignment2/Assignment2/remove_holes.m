function result = remove_holes(image)
%threshold = 10; 
%thresholded = (image > threshold); 

negated = ~image;
labels = bwlabel(negated, 4);
bg = (labels == 1);
negated = negated - bg;
final = negated + image;


result = final;
end