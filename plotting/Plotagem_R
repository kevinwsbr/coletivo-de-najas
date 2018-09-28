comp208_data <- read.table("list_data_comp.txt", header=T, sep="\t") 

# Compute the largest y value used in the data (or we could
# just use range again)
max_y <- max(comp208_data$comparacoesABB, comp208_data$comparacoesAVL)
max_x <- max(comp208_data$tamanhoAVL, comp208_data$tamanhoABB)

# Define colors to be used for AVL and BST
plot_colors <- c("blue","red")

# Start PNG device driver to save output to figure.png
png("figura.png", height=600, width=800, 
    bg="gray")

#Plot list function
plot(comp208_data$tamanhoAVL, comp208_data$comparacoesAVL, type="p", col=plot_colors[1], 
     ylim=c(0,max_y), xlim=c(0,max_x), axes=FALSE, ann=FALSE)
#print(max_x)


# Change interval scale of the axis
axis(1, las=1, at=((max_x %% 1000000)/10)*0:max_x)

axis(2, las=1, at=((max_y %% 1000000)/10)*0:max_y)


box()

# Graph BST with red dashed line and square points
lines(comp208_data$tamanhoABB, comp208_data$comparacoesABB, type="p", pch=22, lty=2, 
      col=plot_colors[2])


# Create a title with a red, bold/italic font
title(main="Search Algorithm: AVL x BST", col.main="black", font.main=4)

# Label the x and y axes with dark green text
title(xlab= "Size", col.lab=rgb(0, 0, 0), cex.lab=1.75, line=2.5)
title(ylab= "Number of Comparisons", col.lab=rgb(0, 0, 0), cex.lab=1.75, line=-2)


namesStruct <- c("AVL", "BST")

legend(1, max_y, namesStruct, cex=0.8, col=plot_colors, 
       pch=21:22, lty=1:2);

# Turn off device driver (to flush output to png)
dev.off()

