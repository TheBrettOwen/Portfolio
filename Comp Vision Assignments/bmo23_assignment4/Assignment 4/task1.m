%%
%Tast 1
%%
%Paths
repo_path = 'D:\cs4379c-fall2021-source';

s = filesep;
addpath([repo_path s 'Code' s '00_common' s '00_detection'])
addpath([repo_path s 'Code' s '00_common' s '00_images'])
addpath([repo_path s 'Code' s '00_common' s '00_utilities'])
addpath([repo_path s 'Code' s '07_skin'])

%%
%Module 1
%%
%Patch 1
frame1 = double(imread('training_A.bmp'));

sample = frame1(122:150, 297:338, :);

sample_red = sample(:, :, 1);
sample_green = sample(:, :, 2);
sample_blue = sample(:, :, 3);

sample_red = sample_red(:);
sample_green = sample_green(:);
sample_blue = sample_blue(:);

sample_vector1 = [sample_red sample_green sample_blue];

%%
%Patch 2
frame2 = double(imread('training_A.bmp'));

sample2 = frame2(246:265, 117:145, :);

sample_red = sample2(:, :, 1);
sample_green = sample2(:, :, 2);
sample_blue = sample2(:, :, 3);

sample_red = sample_red(:);
sample_green = sample_green(:);
sample_blue = sample_blue(:);

sample_vector2 = [sample_red sample_green sample_blue];
%%
%concatonating the patches
final = [sample_vector1;sample_vector2];
final_red = final(:,1,: );
final_green = final(:,2,:);
final_blue = final(:,3,:);

final_red = final_red(:);
final_green = final_green(:);
final_blue = final_blue(:);

%%
%Normalizing
final_total = final_red + final_green + final_blue;
sample_red2 = final_red ./ final_total;
sample_red2(isnan(sample_red2)) = 0; % when (R+G+B) == 0, a division by 0 can result in a NaN
sample_green2 = final_green ./ final_total;
sample_green2(isnan(sample_green2)) = 0;

r_mean = mean(sample_red2);
g_mean = mean(sample_green2);
r_std = std(sample_red2);
g_std = std(sample_green2);

%%
%Testing Module 1
test_frame = double(imread('test.bmp'));
[rows,cols, bands] = size(test_frame);

skin_detection1 = zeros(rows, cols);

for row = 1:rows
    for col = 1:cols
        red = test_frame(row, col, 1);
        green = test_frame(row, col, 2);
        blue = test_frame(row, col, 3);
    
        sum = red+green+blue;
        if sum > 0
            r = red / sum;
            g = green / sum;
        else
            r = 0;
            g = 0;
        end
        
        r_prob = gaussian_probability(r_mean, r_std, r);
        g_prob = gaussian_probability(g_mean, g_std, g);
        prob = r_prob * g_prob;
        skin_detection1(row, col) = prob;
    end
end
final_accuracy = [];
for i = -100:5:350 
        [skin_accuracy, nonskin_accuracy] = eval_module(skin_detection1, i);
        temp_accuracy = [skin_accuracy nonskin_accuracy];
        final_accuracy = [final_accuracy; temp_accuracy]; 
end

a = final_accuracy(:,1);
b = final_accuracy(:,2);

%%
%Module 2
%%
%Patch 1
frame1 = double(imread('training_B.bmp'));

sample = frame1(189:230, 213:293, :);

sample_red = sample(:, :, 1);
sample_green = sample(:, :, 2);
sample_blue = sample(:, :, 3);

sample_red = sample_red(:);
sample_green = sample_green(:);
sample_blue = sample_blue(:);

sample_vector1 = [sample_red sample_green sample_blue];

%%
%Patch 2
frame2 = double(imread('training_B.bmp'));

sample2 = frame2(376:423, 63:120, :);

sample_red = sample2(:, :, 1);
sample_green = sample2(:, :, 2);
sample_blue = sample2(:, :, 3);

sample_red = sample_red(:);
sample_green = sample_green(:);
sample_blue = sample_blue(:);

sample_vector2 = [sample_red sample_green sample_blue];

%%
%Patch 3
frame3 = double(imread('training_B.bmp'));

sample3 = frame3(413:471, 404:455, :);

sample_red = sample3(:, :, 1);
sample_green = sample3(:, :, 2);
sample_blue = sample3(:, :, 3);

sample_red = sample_red(:);
sample_green = sample_green(:);
sample_blue = sample_blue(:);

sample_vector3 = [sample_red sample_green sample_blue];

%%
%concatonating the patches
final = [sample_vector1;sample_vector2];
final_red = final(:,1,: );
final_green = final(:,2,:);
final_blue = final(:,3,:);

final_red = final_red(:);
final_green = final_green(:);
final_blue = final_blue(:);

%%
%Normalizing
final_total = final_red + final_green + final_blue;
sample_red2 = final_red ./ final_total;
sample_red2(isnan(sample_red2)) = 0; % when (R+G+B) == 0, a division by 0 can result in a NaN
sample_green2 = final_green ./ final_total;
sample_green2(isnan(sample_green2)) = 0;

r_mean = mean(sample_red2);
g_mean = mean(sample_green2);
r_std = std(sample_red2);
g_std = std(sample_green2);

%%
%Testing Module 2
skin_detection1 = zeros(rows, cols);

for row = 1:rows
    for col = 1:cols
        red = test_frame(row, col, 1);
        green = test_frame(row, col, 2);
        blue = test_frame(row, col, 3);
    
        sum = red+green+blue;
        if sum > 0
            r = red / sum;
            g = green / sum;
        else
            r = 0;
            g = 0;
        end
        
        r_prob = gaussian_probability(r_mean, r_std, r);
        g_prob = gaussian_probability(g_mean, g_std, g);
        prob = r_prob * g_prob;
        skin_detection1(row, col) = prob;
    end
end
final_accuracy2 = [];
for i = -100:5:350 
        [skin_accuracy, nonskin_accuracy] = eval_module(skin_detection1, i);
        temp_accuracy = [skin_accuracy nonskin_accuracy];
        final_accuracy2 = [final_accuracy2; temp_accuracy]; 
end

c = final_accuracy2(:,1);
d = final_accuracy2(:,2);
%%
%Module 3
neg_hist = read_double_image('negatives.bin');
pos_hist = read_double_image('positives.bin');
result = detect_skin(test_frame, pos_hist, neg_hist); 
result = result*2;
imshow(result, []);
final_accuracy3 = [];
for i = 0:5:100
        [skin_accuracy, nonskin_accuracy] = eval_module(result, i);
        temp_accuracy = [skin_accuracy nonskin_accuracy];
        final_accuracy3 = [final_accuracy3; temp_accuracy]; 
end

e = final_accuracy3(:,1);
f = final_accuracy3(:,2);
%%
%plotting the modules
close all;
figure(1);
plot(a, b, 'k-');
hold on;
plot(c, d, 'r--');
plot(e, f, 'b:');
set(gca, 'XLim', [0 105]);
set(gca, 'YLim', [0 105]);
set(gca, 'XGrid', 'on');
set(gca, 'YGrid', 'on');
xticks([0:10:100])
yticks([0:10:100])
set(gca, 'PlotBoxAspectRatio', [1 1 1]);
legend('Module 1', 'Location', 'NorthWest');
