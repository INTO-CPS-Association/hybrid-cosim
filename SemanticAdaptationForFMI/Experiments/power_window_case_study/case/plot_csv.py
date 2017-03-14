import csv
from bokeh.plotting import figure, output_file, show

color_pallete = [
                "#e41a1c",
                "#377eb8",
                "#4daf4a",
                "#984ea3",
                "#ff7f00",
                "#ffff33",
                "#a65628",
                "#f781bf",
                "#CDD460",
                "#265C70",
                "#622876",
                "#B37737"
                 ]

def plot_csv(filename):
    with open(filename, 'rb') as csvfile:
        rows = csv.reader(csvfile, delimiter=',')
        
        # read all rows at once
        matrixRows = []
        for row in rows:
            matrixRows.append(row)
        
        firstRow = matrixRows[0]
        numVars = len(firstRow) -1 # discount time
        times = []
        vars = []
        for i in range(numVars):
            vars.append([])
        
        for rowIdx in range(len(matrixRows)):
            row = matrixRows[rowIdx]
            times.append(float(row[0]))
            for varIdx in range(1, numVars):
                col = row[varIdx]
                vars[varIdx].append(float(col))
        
        plot_file = filename.replace(".csv", ".html")
        output_file(plot_file, title="Results")
        
        p = figure(title="Plot", x_axis_label='time', y_axis_label='', width=1300, height=900)
        
        varName = "v{0}"
        for i in range(numVars):
            p.line(x=times, y=vars[i], legend=varName.format(i), color=color_pallete[i])
    
        show(p)
        
plot_csv('result_power_sa.csv')
plot_csv('result_ENV.csv')
plot_csv('result_Control_sa.csv')
