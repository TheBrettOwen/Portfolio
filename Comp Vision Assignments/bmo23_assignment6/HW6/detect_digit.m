function [first, second] = detect_digit(image, template) 

result = normalized_correlation(image, template);
figure(3); imshow(result, []);
a= result(:);
a = max(a);
[row, col] = find( result == a);

image = draw_rectangle2((image * 5), row, col, 28,28);
figure(1); imshow(image ); 
first = row;
second = col;
end 