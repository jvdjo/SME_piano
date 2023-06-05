using System.ComponentModel.DataAnnotations.Schema;
using Microsoft.EntityFrameworkCore;

namespace SME.Models;

[PrimaryKey("Id")]
[Table("Frequencia")]
public class Frequencia
{

    public Guid Id { get; set; } = Guid.NewGuid();
    public int FrequenciaNota { get; set; }
    public DateTime Data { get; set; }
}