#Gràfics bàsics
library(ggplot2)

dimensions <- c("K2", "K3", "K4", "K5", "K6")

# Directori per desar fitxers PNG
output_directory <- "img"

# Crear el directori de sortida si no existeix
if (!dir.exists(output_directory)) {
  dir.create(output_directory)
}
for (dim in dimensions) {
  data_list <- list()

  tree_types <- c("Squarish", "Standard", "Relaxed")

  for (tree_type in tree_types) {
    file_name <- paste0(tree_type, dim, ".csv")
    data <- read.csv(file_name)
    data$Type <- tree_type  

    data_list[[tree_type]] <- data
  }

  # Create the plot for the current dimension
  title <- bquote(paste("Relació entre mitjana de nodes visitats per consulta i nodes del kd-tree de dimensió ", .(dim)))

  p <- ggplot() +
    geom_line(data = data_list$Squarish, aes(x = N, y = Mean, color = "Squarish")) +
    geom_line(data = data_list$Standard, aes(x = N, y = Mean, color = "Standard")) +
    geom_line(data = data_list$Relaxed, aes(x = N, y = Mean, color = "Relaxed")) +
    labs(
      title = title,
      x = "Nodes de l'arbre",
      y = "Mitjana de nodes visitats per consulta"
    ) +
       scale_color_manual(values = c("Squarish" = "red", "Standard" = "blue", "Relaxed" = "green"),
                       name = "Tipus de l'arbre") +
    scale_fill_manual(values = c("Squarish" = "red", "Standard" = "blue", "Relaxed" = "green"))+
    scale_y_continuous(limits = c(0, NA))

  output_file <- file.path(output_directory, paste0( dim, ".png"))
  # Desar el grafic com a fitxer PNG
  ggsave(output_file, plot = p, width = 8, height = 6)  
}



#Totes les gràfiques en el mateix
library(ggplot2)

data_list <- list()

dimensions <- c("K2", "K3", "K4", "K5", "K6")

# Directori per desar fitxers PNG
output_directory <- "img"

# Crear el directori de sortida si no existeix
if (!dir.exists(output_directory)) {
  dir.create(output_directory)
}

tree_types <- c("Squarish", "Standard", "Relaxed")

for (dim in dimensions) {
  for (tree_type in tree_types) {
    file_name <- paste0(tree_type, dim, ".csv")
    data <- read.csv(file_name)
    data$Dim <- dim  
    data$Type <- tree_type  
    data_list[[paste(dim, tree_type, sep = "_")]] <- data
  }
}

# Combinar dades
combined_data <- do.call(rbind, data_list)

#Gràfica
p <- ggplot(combined_data, aes(x = N, y = Mean, group = Type, color = Type)) +
  geom_line() +
  facet_wrap(~Dim, scales = "free_y") +  
  #"free_y" per escalar l'eix y de manera dinàmica
  labs(
    title = "Relació entre mitjana de nodes visitats per consulta i nodes del kd-tree de dimensió ",
    x = "Número de nodes de l'arbre",
    y = "Mitjana de nodes visitats per consulta"
  ) +
  theme(strip.text.x = element_text(size = 8)) + 
  # Ajusteu la mida de les etiquetes de l'eix X
     scale_color_manual(values = c("Squarish" = "red", "Standard" = "blue", "Relaxed" = "green"),
                       name = "Tipus de l'arbre") +
    scale_fill_manual(values = c("Squarish" = "red", "Standard" = "blue", "Relaxed" = "green"))+
    scale_y_continuous(limits = c(0, NA))
 output_file <- file.path(output_directory, paste0("combinedPlots", dim, ".png"))

# Desar el grafic com a fitxer PNG
ggsave(output_file, plot = p, width = 12, height = 9)




# Per gràfics amb desviacions estándard
library(ggplot2)

dimensions <- c("K2", "K3", "K4", "K5", "K6")

# Directori per desar fitxers PNG
output_directory <- "img"

# Crear el directori de sortida si no existeix
if (!dir.exists(output_directory)) {
  dir.create(output_directory)
}

# Llegir i processar les dades per cada dimensió
for (dim in dimensions) {
  data_list <- list()

  tree_types <- c("Squarish", "Standard", "Relaxed")

  for (tree_type in tree_types) {
    file_name <- paste0(tree_type, dim, ".csv")
    data <- read.csv(file_name)
    data$Type <- tree_type  
    data_list[[tree_type]] <- data
  }

  title <- bquote(paste("Relació entre Nodes visitats i nodes de l'arbre de dimensió ", .(dim)))

  p <- ggplot() +
    geom_line(data = data_list$Squarish, aes(x = N, y = Mean, color = "Squarish")) +
    geom_line(data = data_list$Standard, aes(x = N, y = Mean, color = "Standard")) +
    geom_line(data = data_list$Relaxed, aes(x = N, y = Mean, color = "Relaxed")) +
    
    geom_errorbar(data = data_list$Squarish, aes(x = N, ymin = Mean - sqrt(data_list$Squarish$Variance), ymax = Mean + sqrt(data_list$Squarish$Variance), color = "Squarish"), width = 0) +
    geom_errorbar(data = data_list$Standard, aes(x = N, ymin = Mean - sqrt(data_list$Standard$Variance), ymax = Mean + sqrt(data_list$Standard$Variance), color = "Standard"), width = 0) +
    geom_errorbar(data = data_list$Relaxed, aes(x = N, ymin = Mean - sqrt(data_list$Relaxed$Variance), ymax = Mean + sqrt(data_list$Relaxed$Variance), color = "Relaxed"), width = 0)  +
    labs(
      title = title,
      x = "Nodes de l'arbre",
      y = "Mitjana de nodes visitats per consulta"
    ) +
    scale_color_manual(values = c("Squarish" = "red", "Standard" = "blue", "Relaxed" = "green"),
                       name = "Tipus de l'arbre") +
    scale_y_continuous(limits = c(0, NA))


  output_file <- file.path(output_directory, paste0(dim, "withStandardDev.png"))
  # Desar el grafic com a fitxer PNG
  ggsave(output_file, plot = p, width = 8, height = 6) 
}



library(minpack.lm)
library(ggplot2)
dimensions <- c("K2", "K3", "K4", "K5", "K6")
tree_types <- c("Standard", "Squarish", "Relaxed")
# Directori per desar fitxers PNG
output_directory <- "img"

# Crear el directori de sortida si no existeix
if (!dir.exists(output_directory)) {
  dir.create(output_directory)
}
# Recorre cada type_tree
for (tree_type in tree_types) {
  # Crear una llista per emmagatzemar els resultats de tots els valors K
all_results <- list()

result_file <- paste("all_estimated_values_", tree_type, ".csv", sep = "")

# Check if the file exists
if (file.exists(result_file)) {
  # Si el fitxer existeix, eliminar-ho per començar de nou
  file.remove(result_file)
}

# Recorre cada valor K
for (dim in dimensions) {
  file_name <- paste(tree_type, dim, ".csv", sep="")
  data <- read.csv(file_name)

# Ajustar la corba utilitzant nlsLM per estimar els paràmetres A, B i z LM es un algorisme d'optimització utilitzat per ajustar models no lineals

# L'equació del model és Mean' = A * N^z + B * log(N)
# - data: el conjunt de dades per ajustar el model
# - start: estimacions inicials dels paràmetres (A, B i z)
# - lower: límits inferiors per als paràmetres (1 per A i B, 0 per z)
# - upper: límits superiors per als paràmetres (no hi ha límit superior per a A i B, 0,999 per a z per limitar-lo <1)
# - control: paràmetres de control per a nls.lm, inclòs el nombre màxim d'iteracions (100)

  fit <- nlsLM(Mean ~ A * N^z + B * log(N), data = data, start = c(A = 1, B = 1, z = 0), lower = c(0, 1, 0), upper = c(Inf, 1, 0.999), control = nls.lm.control(maxiter = 100))

  A_estimate <- coef(fit)["A"]
  B_estimate <- coef(fit)["B"]
  z_estimate <- coef(fit)["z"]

  # Store the estimated values for the current K
  result_key <- paste("K", dim)
  result <- c(Dimension = dim,A = A_estimate, B = B_estimate, z = z_estimate)
  all_results[[result_key]] <- result

  x_seq <- seq(min(data$N), max(data$N), length.out = 100)
  curve_values <- log(A_estimate * x_seq^z_estimate + B_estimate * log(x_seq)) / log(data$N)
  plot_title_loglog <- paste("Log-Log Plot de C'(N) per", tree_type, dim)
  img_path_loglog <- file.path("img", paste0(tree_type, "_loglog_plot", dim, ".png"))

  png(filename = img_path_loglog, width = 800, height = 600)
  plot(x_seq, curve_values, type = "l", xlab = "log(N)", ylab = "log(C'(N))", main = plot_title_loglog)
  dev.off()

  curve_values_ratio <- log(A_estimate * x_seq^z_estimate + B_estimate * log(x_seq)) / log(x_seq)
  plot_title_ratio <- paste("Plot de log(C'(N))/log(N) per", tree_type, dim)
  img_path_ratio <- file.path("img", paste0(tree_type, "_logratio_plot", dim, ".png"))

  png(filename = img_path_ratio, width = 800, height = 600)
  plot(x_seq, curve_values_ratio, type = "l", xlab = "log(x)", ylab = "log(y)", main = plot_title_ratio)
  dev.off()
}

# Desar dades a partir dels valors estimats
results_df <- data.frame(t(sapply(all_results, function(x) unlist(x))))

# Desar de dades en un fitxer CSV sense cometes
write.csv(results_df, result_file, row.names = FALSE, quote = FALSE)

cat("All estimated values for", tree_type, "and dimension", dim, "saved to", result_file, "\n")

}