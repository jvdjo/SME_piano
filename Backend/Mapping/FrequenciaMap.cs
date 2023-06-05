using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using SME.Models;

namespace SME.Mapping;

public class FrequenciaMap : IEntityTypeConfiguration<Frequencia>
{
    public void Configure(EntityTypeBuilder<Frequencia> builder)
    {
        builder.HasKey(l => l.Id);
    }
}