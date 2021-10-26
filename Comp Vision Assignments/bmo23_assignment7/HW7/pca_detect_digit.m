function [row,column] = pca_detect_digit(inImage, mean_digit, eigenvectors, N)
scores = zeros(32, 32);
for i = 1:32
    for j = 1:32
        imax = i + 28;
        jmax = j+28;
        window = inImage(i:imax, j:jmax);
        scores(i, j) = pca_score(window, mean_digit, eigenvectors, N);
    end
end 

lowest = min(min(scores));
[row, column] = find(scores == lowest);
boxImage = draw_rectangle2(inImage, row, column, 28, 28); 
imshow(boxImage, []);
end

