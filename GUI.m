classdef con3 < matlab.apps.AppBase 
    % Properties that correspond to app components 
    properties (Access = public) 
        UIFigure      matlab.ui.Figure 
        SwitchLabel   matlab.ui.control.Label 
        Switch        matlab.ui.control.ToggleSwitch 
        Switch2Label  matlab.ui.control.Label 
        Switch2       matlab.ui.control.ToggleSwitch 
    end 
    methods (Access = private) 
        function SwitchValueChanged(app, event) 
            value = app.Switch.Value; 
            channelID = 811395; 
            if strcmp(value,'On') 
             
thingSpeakWrite(channelID,'Fields',[6],'Values',{1},'WriteKey','AE9YBCK1NH
 DTQJS0','Timeout',5) 
           else 
             
thingSpeakWrite(channelID,'Fields',[6],'Values',{0},'WriteKey','AE9YBCK1NH
 DTQJS0','Timeout',5) 
           end  
        end 
        % Value changed function: Switch2 
        function Switch2ValueChanged(app, event) 
            value = app.Switch2.Value; 
            channelID = 811395; 
            if strcmp(value,'On') 
             
thingSpeakWrite(channelID,'Fields',[7],'Values',{1},'WriteKey','AE9YBCK1NH
 DTQJS0','Timeout',5) 
           else
           thingSpeakWrite(channelID,'Fields',[7],'Values',{0},'WriteKey','AE9YBCK1NH
 DTQJS0','Timeout',5) 
           end  
        end 
    end 
    % App initialization and construction 
    methods (Access = private) 
                function createComponents(app) 
                        app.UIFigure = uifigure; 
            app.UIFigure.Position = [100 100 640 480]; 
            app.UIFigure.Name = 'UI Figure'; 
            % Create SwitchLabel 
            app.SwitchLabel = uilabel(app.UIFigure); 
            app.SwitchLabel.HorizontalAlignment = 'center'; 
            app.SwitchLabel.Position = [185 179 41 22]; 
            app.SwitchLabel.Text = 'Switch'; 
            % Create Switch 
            app.Switch = uiswitch(app.UIFigure, 'toggle'); 
            app.Switch.ValueChangedFcn = createCallbackFcn(app, 
@SwitchValueChanged, true); 
            app.Switch.Position = [195 237 20 45]; 
            % Create Switch2Label 
            app.Switch2Label = uilabel(app.UIFigure); 
            app.Switch2Label.HorizontalAlignment = 'center'; 
            app.Switch2Label.Position = [334 179 47 22]; 
            app.Switch2Label.Text = 'Switch2'; 
            % Create Switch2 
            app.Switch2 = uiswitch(app.UIFigure, 'toggle'); 
            app.Switch2.ValueChangedFcn = createCallbackFcn(app, 
@Switch2ValueChanged, true); 
            app.Switch2.Position = [348 237 20 45]; 
        end 
    end 
    methods (Access = public) 
                function app = con3 
                        createComponents(app) 
                        registerApp(app, app.UIFigure) 
            if nargout == 0 
                clear app 
            end 
        end 
                function delete(app) 
             
        end 
    end 
end
