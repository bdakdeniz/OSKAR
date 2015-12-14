function plot_uv(vis, time_range, baseline_range)

if (nargin < 1)
    error('OSKAR:argChk', ...
        [...
        '\nERROR:\n' ...
        '\tIncorrect number of input arguments.\n\n' ... 
        'Usage:\n'...
        '\toskar.visibilities.plot_uv(vis, <time_range>, <baseline_range>)\n\n' ...
        '' ...
        'Arguments:\n' ...
        '\t1) vis (required): OSKAR MATLAB visibility structure.\n' ...
        '\t2) time_range (optional): time range to plot, \n'...
        '\t   e.g. [1 2], default = [1 vis.num_times]\n' ...
        '\t3) baseline_range (optional): baseline range to plot, \n'...
        '\t   e.g. [1 2]. default = [1 vis.num_baselines]\n' ...
        '\n' ...
        'Example: \n' ...
        '\toskar.visibilities.plot_uv(vis)\n' ...
        '\toskar.visibilities.plot_uv(vis, [1 2])\n' ...
        '\tfor i = 1:vis.num_times\n' ...
        '\t    oskar.visibilities.plot_uv(vis, [i i]);\n' ...
        '\t    xlim([-max(vis.uu(:)) max(vis.uu(:))] * 1.2e-3);\n' ...
        '\t    ylim([-max(vis.vv(:)) max(vis.vv(:))] * 1.2e-3);\n' ...
        '\t    drawnow;\n' ...
        '\t    i = i + 1;\n' ...
        '\tend\n' ...
        ]); 
end

if (~isstruct(vis))
    error('argument vis must be an OSKAR visibilities structure');
end



if ~exist('time_range', 'var')
    time_range = [1 vis.num_times];
elseif (length(time_range) ~= 2)
    time_range = [time_range time_range];
end

if ~exist('baseline_range', 'var')
    baseline_range = [1 vis.num_baselines];
elseif (length(baseline_range) ~= 2)
    baseline_range = [baseline_range baseline_range];
end

b = [baseline_range(1) baseline_range(2)];
t = [time_range(1) time_range(2)];
uu = vis.uu(b(1):b(2),t(1):t(2));
vv = vis.vv(b(1):b(2),t(1):t(2));
uu = [uu(:); -uu(:)];
vv = [vv(:); -vv(:)];
uu = uu./1.0e3;
vv = vv./1.0e3;

scatter(uu, vv, 5, [0 0 1], 'filled');
str_title = ['UV Plot (' sprintf('%s', vis.filename) ')'];
if (time_range(1) == 0 && time_range(2) == vis.num_times)
    str_title = {str_title; [num2str(length(uu(:))) ' visibilities']};
elseif (time_range(1) == time_range(2))
    str_title = {str_title; ...
        ['time: ' num2str(time_range(1)) ', ' ...
        num2str(length(uu(:))) ' visibilities']};
else
    str_title = {str_title; ...
        ['time: ' num2str(time_range(1)) ' to ' ...
        num2str(time_range(2)) ...
        ', ' num2str(length(uu(:))) ' visibilities']};
end
title(str_title, 'Interpreter', 'none');
xlabel('baseline uu (kilometres)');
ylabel('baseline vv (kilometres)');
axis square;

end
