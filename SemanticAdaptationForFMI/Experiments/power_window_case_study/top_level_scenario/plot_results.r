library(ggplot2)
library(cowplot)
library(grid)
library(dplyr)
library(plyr)
library(reshape)
library(plotly)
library(stringr)

sizeAxisLabel <- 26

# Plot environment
  env <- read.csv("result_ENV.csv")
  
  # Drop columns that will not be plotted
  env$ddown <- NULL
  env$ddown_stop <- NULL
  env$pup <- NULL
  env$pup_stop <- NULL
  env$pdown <- NULL
  env$pdown_stop <- NULL
  env$obj <- NULL
  
  env_molten <- melt(env, id=c("t"))
  
  pdf("results_Env.pdf", width=10, height=5)
  
  pallete <- c("#89cbaf",
               "#be5440")
  penv <- ggplot(data=env_molten) +
            geom_line(aes(x=t, y=value, color=variable), size=2) +
            scale_x_continuous("Time (s)") +
            scale_y_discrete("Value", limits=c(0, 1), labels=c("0"="False", "1"="True")) +
            scale_color_manual("environment",
                               labels=c("dup"="driver_up","dup_stop"="driver_stop"),
                               values = pallete) +
            theme(axis.title.y=element_blank(),
                  axis.title=element_text(size=sizeAxisLabel,face="bold"),
                  axis.text=element_text(size=sizeAxisLabel),
                  legend.text=element_text(size=sizeAxisLabel),
                  legend.title=element_text(size=sizeAxisLabel,face="bold"))
  penv
  
  dev.off()

# Plot Controller 
  control <- read.csv("result_Control_sa.csv")
  control_molten <- melt(control, id=c("t"))
  
  pdf("results_Control_sa.pdf", width=10, height=5)
  
  pallete <- c("#9699c3",
               "#cca956")
  pcontrol <- ggplot(data=control_molten) +
                geom_line(aes(x=t, y=value, color=variable), size=1) +
                scale_x_continuous("Time (s)") +
                scale_y_continuous("Value", limits=c(0, 1)) +
                scale_color_manual("controller_sa",
                                   values = pallete) +
                theme(axis.title.y=element_blank(),
                      axis.title=element_text(size=sizeAxisLabel,face="bold"),
                      axis.text=element_text(size=sizeAxisLabel),
                      legend.text=element_text(size=sizeAxisLabel),
                      legend.title=element_text(size=sizeAxisLabel,face="bold"))
    
  pcontrol
  
  dev.off()
  
# Plot power 
  power <- read.csv("result_power_sa.csv")
  power$omega <- NULL
  power$theta <- NULL
  power_molten <- melt(power, id=c("t"))
  
  pdf("results_power_sa.pdf", width=10, height=5)
  
  pallete <- c("#4f314e")
  ppower <- ggplot(data=power_molten) +
            geom_line(aes(x=t, y=value, color=variable), size=1) +
            scale_x_continuous("Time (s)") +
            scale_y_continuous("Value") +
            scale_color_manual("power_sa",
                               labels=c("i"="armature_current"),
                               values = pallete) +
            theme(axis.title.y=element_blank(),
                  axis.title=element_text(size=sizeAxisLabel,face="bold"),
                  axis.text=element_text(size=sizeAxisLabel),
                  legend.text=element_text(size=sizeAxisLabel),
                  legend.title=element_text(size=sizeAxisLabel,face="bold"))
  ppower
  
  dev.off()
  
# Plot Loop_sa
  loop <- read.csv("result_loop_sa.csv")
  loop$tau <- NULL
  loop_molten <- melt(loop, id=c("t"))
  
  pdf("results_loop_sa.pdf", width=10, height=5)
  
  pallete <- c("#89cbaf",
               "#be5440",
               "#9699c3",
               "#cca956",
               "#4f314e")
  ploop <- ggplot(data=loop_molten) +
            geom_line(aes(x=t, y=value, color=variable), size=1) +
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
  ploop
  
  dev.off()
  
# Make multi-grid plot
  row_plot <- plot_grid(penv, pcontrol, ppower, ploop, nrow = 4, ncol = 1, align = "v")
  save_plot("vertical_plot.pdf", row_plot, nrow = 4, ncol = 1, base_aspect_ratio = 2)
  