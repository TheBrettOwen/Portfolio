function result = oriented_edges(img, sigma, threshold, direction, tolerance)
grey_img = read_gray(img);

thetas = gradient_orientations(grey_img, sigma);

dx = [-1 0 1; -2 0 2; -1 0 1] / 8;
dy = dx';

rot_forward = imrotate(dx, direction - tolerance, 'bilinear', 'loose');
rot_forward = rot_forward / sum(sum(abs(rot_forward)));
rot_backward = imrotate(dx, direction + tolerance, 'bilinear', 'loose');
rot_backward = rot_backward / sum(sum(abs(rot_backward)));

blurred_gray = imfilter(grey_img, fspecial('gaussian', 9, 1.4), 'symmetric');
direction1_grey = imfilter(blurred_gray, rot_forward, 'symmetric');
direction2_grey = imfilter(blurred_gray, rot_backward, 'symmetric');

grad_norms = (direction1_grey.^2 + direction2_grey.^2).^0.5;

thinned = nonmaxsup(grad_norms, thetas, 1.35);
thresholded = hysthresh(thinned, threshold, 2*threshold);

img_canny = canny(grey_img, threshold);

result = (thresholded & img_canny);
end