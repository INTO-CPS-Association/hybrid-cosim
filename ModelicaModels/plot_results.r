library(ggplot2)
library(cowplot)
library(grid)
library(dplyr)
library(plyr)
library(reshape)
library(plotly)
library(stringr)

sizeAxisLabel <- 22

# Gather all results
data <- read.csv("controller_scenario_export.csv")

data_molten <- melt(data, id=c("time"))



# Plot Controller 
  control <- subset(data_molten, variable == "controller.u_motor" | variable == "controller.d_motor")
  
  pallete <- c("#9699c3",
               "#cca956")
  pcontrol <- ggplot(data=control) +
                geom_line(aes(x=time, y=value, color=variable, linetype=variable), size=1) +
                scale_x_continuous("Time (s)") +
                scale_y_continuous("Value", limits=c(0, 1)) +
                scale_color_manual("controller",
                                   labels=c("controller.u_motor"="u","controller.d_motor"="d"),
                                   values = pallete) +
                guides(color = guide_legend(override.aes = list(linetype = c('solid', 'dashed'))),
                      linetype = FALSE) + 
                theme(axis.title.y=element_blank(),
                      axis.title=element_text(size=sizeAxisLabel,face="bold"),
                      axis.text=element_text(size=sizeAxisLabel),
                      legend.text=element_text(size=sizeAxisLabel),
                      legend.title=element_text(size=sizeAxisLabel,face="bold"))
    
  pcontrol
  
# Plot power 
  power <- subset(data_molten, variable == "controller.i")
  
  pallete <- c("#4f314e")
  ppower <- ggplot(data=power) +
            geom_line(aes(x=time, y=value, color=variable), size=1) +
            scale_x_continuous("Time (s)") +
            scale_y_continuous("Value", limits=c(-5, 10)) +
            scale_color_manual("power",
                               labels=c("controller.i"="armature_current"),
                               values = pallete) +
            theme(axis.title.y=element_blank(),
                  axis.title=element_text(size=sizeAxisLabel,face="bold"),
                  axis.text=element_text(size=sizeAxisLabel),
                  legend.text=element_text(size=sizeAxisLabel),
                  legend.title=element_text(size=sizeAxisLabel,face="bold"))
  ppower
  
# Plot window
  window <- subset(data_molten, variable == "window.displacement")
  
  pallete <- c("#be5440")
  pwindow <- ggplot(data=window) +
            geom_line(aes(x=time, y=value, color=variable), size=1) +
            scale_x_continuous("Time (s)") +
            scale_y_continuous("Value") +
            scale_color_manual("window_sa",
                               labels=c("height"="disp"),
                               values = pallete) +
            theme(axis.title.y=element_blank(),
                  axis.title=element_text(size=sizeAxisLabel,face="bold"),
                  axis.text=element_text(size=sizeAxisLabel),
                  legend.text=element_text(size=sizeAxisLabel),
                  legend.title=element_text(size=sizeAxisLabel,face="bold"))
  pwindow
  
# Make multi-grid plot
  row_plot <- plot_grid(pcontrol, ppower, pwindow, nrow = 3, ncol = 1, align = "v")
  save_plot("vertical_plot_monolithic.pdf", row_plot, nrow = 3, ncol = 1, base_aspect_ratio = 3)
  